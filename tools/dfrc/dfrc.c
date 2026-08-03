#include <byteswap.h>
#include <ctype.h>
#include <elf.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------------------------------------------------------------------------------------

typedef struct _dfr_action_t {
    char *elf_filename; /* maybe owned */
    bool elf_filename_owned;

    char *elf_section; /* maybe owned */
    bool elf_section_owned;

    int offset;
    int min_length;
    int max_length;
    bool replace_zeroes;
} dfr_action_t;

// --------------------------------------------------------------------------------------------------------------------

typedef struct _elf_section_t {
    uint32_t virt_addr;
    uint32_t file_offset;
    uint32_t size;
    uint8_t *data;
} elf_section_t;

// --------------------------------------------------------------------------------------------------------------------

const char *g_elfBasePath = nullptr;

// --------------------------------------------------------------------------------------------------------------------

#define CLOSE_AND_RESET(f) \
    do { if ((f)) { fclose((f)); (f) = nullptr; } } while(0)

int max_int(int a, int b)
    { return a > b ? a : b; }
int min_int(int a, int b)
    { return a < b ? a : b; }

// --------------------------------------------------------------------------------------------------------------------

char *skip_whitespace(const char *str) {
    while (*str != '\0' && isspace(*str))
        str++;
    return (char *) str;
}

// --------------------------------------------------------------------------------------------------------------------

void remove_trailing_whitespace(char *str) {
    int last_idx = strlen(str) - 1;
    while (last_idx >= 0 && isspace(str[last_idx]))
        str[last_idx--] = '\0';
}

// --------------------------------------------------------------------------------------------------------------------

void remove_newline(char *str) {
    while (*str != '\0') {
        if (*str == '\r' || *str == '\n') {
            *str = '\0';
            return;
        }
        str++;
    }
}

// --------------------------------------------------------------------------------------------------------------------

char *remove_whitespace(char *str) {
    str = skip_whitespace(str);
    remove_trailing_whitespace(str);
    return str;
}

// --------------------------------------------------------------------------------------------------------------------

bool elf_read_section(FILE *elf_file, const char *section_name, elf_section_t *sec_out) {
    Elf32_Ehdr elf_header;
    if (fread(&elf_header, sizeof(elf_header), 1, elf_file) != 1) {
        fprintf(stderr, "couldn't read .ELF header\n");
        return false;
    }

    // Check the magic number to ensure it's a valid ELF file
    if (elf_header.e_ident[EI_MAG0] != ELFMAG0 ||
        elf_header.e_ident[EI_MAG1] != ELFMAG1 ||
        elf_header.e_ident[EI_MAG2] != ELFMAG2 ||
        elf_header.e_ident[EI_MAG3] != ELFMAG3)
    {
        fprintf(stderr, "not a valid .ELF file\n");
        return false;
    }

    // Swap bytes for big endian files (assuming little endian host)
    bool is_big_endian = (elf_header.e_ident[EI_DATA] == ELFDATA2MSB);
    if (is_big_endian) {
        elf_header.e_type      = bswap_16(elf_header.e_type);
        elf_header.e_machine   = bswap_16(elf_header.e_machine);
        elf_header.e_version   = bswap_32(elf_header.e_version);
        elf_header.e_entry     = bswap_32(elf_header.e_entry);
        elf_header.e_phoff     = bswap_32(elf_header.e_phoff);
        elf_header.e_shoff     = bswap_32(elf_header.e_shoff);
        elf_header.e_flags     = bswap_32(elf_header.e_flags);
        elf_header.e_ehsize    = bswap_16(elf_header.e_ehsize);
        elf_header.e_phentsize = bswap_16(elf_header.e_phentsize);
        elf_header.e_phnum     = bswap_16(elf_header.e_phnum);
        elf_header.e_shentsize = bswap_16(elf_header.e_shentsize);
        elf_header.e_shnum     = bswap_16(elf_header.e_shnum);
        elf_header.e_shstrndx  = bswap_16(elf_header.e_shstrndx);
    }

    // Read all section headers
    Elf32_Shdr *sec_headers = malloc(elf_header.e_shnum * sizeof(Elf32_Shdr));
    fseek(elf_file, elf_header.e_shoff, SEEK_SET);
    fread(sec_headers, sizeof(Elf32_Shdr), elf_header.e_shnum, elf_file);

    // Get the section header string table
    Elf32_Shdr *str_table_header = &sec_headers[elf_header.e_shstrndx];
    if (is_big_endian) {
        str_table_header->sh_offset = bswap_32(str_table_header->sh_offset);
        str_table_header->sh_size   = bswap_32(str_table_header->sh_size);
    }

    char *str_table = malloc(str_table_header->sh_size);
    fseek(elf_file, str_table_header->sh_offset, SEEK_SET);
    fread(str_table, 1, str_table_header->sh_size, elf_file);

    // Search for the section by name
    bool found = false;
    for (int i = 0; i < elf_header.e_shnum; i++) {
        if (is_big_endian) {
            sec_headers[i].sh_name   = bswap_32(sec_headers[i].sh_name);
            sec_headers[i].sh_addr   = bswap_32(sec_headers[i].sh_addr);
            sec_headers[i].sh_offset = bswap_32(sec_headers[i].sh_offset);
            sec_headers[i].sh_size   = bswap_32(sec_headers[i].sh_size);
        }

        const char *name = &str_table[sec_headers[i].sh_name];

        if (strcmp(name, section_name) == 0) {
            Elf32_Shdr *sec_header = &(sec_headers[i]);

            sec_out->virt_addr   = sec_header->sh_addr;
            sec_out->file_offset = sec_header->sh_offset;
            sec_out->size        = sec_header->sh_size;
            sec_out->data        = malloc(sec_header->sh_size);

            fseek(elf_file, sec_header->sh_offset, SEEK_SET);
            fread(sec_out->data, 1, sec_header->sh_size, elf_file);

            found = true;
            break;
        }
    }

    free(str_table);
    free(sec_headers);

    if (!found) {
        fprintf(stderr, "section '%s' not found\n", section_name);
        return false;
    }

    return true;
}

// --------------------------------------------------------------------------------------------------------------------

void dfr_action_deinit(dfr_action_t *action) {
    if (action == nullptr)
        return;

    #define FREE_STRING_IF_USED(NAME) \
        do { \
            if (action->NAME##_owned) { \
                if (action->NAME) \
                    free (action->NAME); \
                action->NAME##_owned = false; \
            } \
            action->NAME = nullptr; \
        } while (0)

    // Deallocate memory.
    FREE_STRING_IF_USED(elf_filename);
    FREE_STRING_IF_USED(elf_section);
}

// --------------------------------------------------------------------------------------------------------------------

bool dfr_action_init(dfr_action_t *action, const char *line) {
    memset(action, 0, sizeof(dfr_action_t));

    char arg_buf[65536];
    snprintf(arg_buf, sizeof(arg_buf), "%s", line);

    char *arg = nullptr;
    char *next_arg = skip_whitespace(arg_buf);
    if (*next_arg == '\0') {
        fprintf(stderr, "empty DFR action\n");
        return false;
    }

    while (next_arg != nullptr) {
        arg = next_arg;
        char *space = arg;

        // Get the first whitespace character...
        while (*space != '\0' && !isspace(*space))
            space++;
        // ...and replace all the whitespace there with \0.
        while (*space != '\0' && isspace(*space)) {
            *space = '\0';
            space++;
        }
        // If there's more to the string, track it.
        next_arg = (*space == '\0') ? nullptr : space;

        // Break parameter into 'left=right'.
        char *left = arg, *right = nullptr;
        char *eq = strchr(arg, '=');
        if (eq != nullptr) {
            *eq = '\0';
            right = eq + 1;
        }
        else
            right = "";

        #define REPLACE_STRING(NAME) \
            do { \
                if (action->NAME##_owned) { \
                    if (action->NAME) \
                        free (action->NAME); \
                } \
                action->NAME = strdup(right); \
                action->NAME##_owned = true; \
            } while (0)

        if (strcmp(left, "elf") == 0)
            REPLACE_STRING(elf_filename);
        else if (strcmp(left, "section") == 0)
            REPLACE_STRING(elf_section);
        else if (strcmp(left, "offset") == 0)
            action->offset = strtol(right, nullptr, 0);
        else if (strcmp(left, "min_length") == 0)
            action->min_length = abs(strtol(right, nullptr, 0));
        else if (strcmp(left, "max_length") == 0)
            action->max_length = abs(strtol(right, nullptr, 0));
        else if (strcmp(left, "length") == 0) {
            action->min_length = abs(strtol(right, nullptr, 0));
            action->max_length = action->min_length;
        }
        else if (strcmp(left, "replace_zeroes") == 0)
            action->replace_zeroes = true;
        else {
            fprintf(stderr, "unknown action parameter '%s'\n", left);
            dfr_action_deinit(action);
            return false;
        }
    }

    return true;
}

// --------------------------------------------------------------------------------------------------------------------

bool print_new_dfr_patch(
    dfr_action_t *action, FILE *orig_file, FILE *elf_file, FILE *file_out, const char *dfr_in_line
) {
    bool rval = true;

    if (elf_file == nullptr) {
        fprintf(stderr, "%s: .ELF file not provided\n", dfr_in_line);
        rval = false;
        goto error_quit;
    }
    if (action->elf_section == nullptr) {
        fprintf(stderr, "%s: 'section' must be set\n", dfr_in_line);
        rval = false;
        goto error_quit;
    }

    elf_section_t section = {};
    if (!elf_read_section(elf_file, action->elf_section, &section)) {
        rval = false;
        goto error_quit;
    }

    bool orig_zeroes = action->replace_zeroes;
    if (orig_file == nullptr)
        orig_zeroes = true;
    bool bin_zeroes = false;

    uint8_t orig_buf[16] = {};
    uint8_t bin_buf[16]  = {};

    int orig_offset = action->offset;
    int bin_remaining = section.size;
    const uint8_t *bin_data = section.data;

    // Use the entire binary data length or, if provided, the max length.
    if (action->max_length > 0 && bin_remaining > action->max_length) {
        fprintf(stderr, "%s: section '%s' size (0x%x bytes) exceeded max_length\n",
            dfr_in_line, action->elf_section, bin_remaining);
        rval = false;
        goto error_quit;
    }

    // Make sure to always read at least 'min_length' bytes.
    int length = max_int(action->min_length, bin_remaining);

    for (; length > 0; length -= 0x10) {
        // Get original data.
        int orig_bytes_read = 0;
        if (!orig_zeroes) {
            auto orig_to_read = min_int(length, sizeof(orig_buf));
            orig_bytes_read = max_int(0, fread(orig_buf, 1, orig_to_read, orig_file));
            if (orig_bytes_read < sizeof(orig_buf))
                orig_zeroes = true;
        }
        for (int i = orig_bytes_read; i < sizeof(orig_buf); i++)
            orig_buf[i] = '\0';

        // Get replacement data.
        int bin_to_read = 0;
        if (!bin_zeroes) {
            bin_to_read = min_int(min_int(bin_remaining, length), sizeof(bin_buf));
            bin_remaining = max_int(0, bin_remaining - 0x10);
            for (int i = 0; i < bin_to_read; i++)
                bin_buf[i] = *(bin_data++);
            if (bin_remaining == 0)
                bin_zeroes = true;
        }
        else
            bin_to_read = 0;
        for (int i = bin_to_read; i < sizeof(bin_buf); i++)
            bin_buf[i] = '\0';

        // Print the line, starting with the file offset.
        fprintf(file_out, "%05x,", orig_offset);
        orig_offset += 0x10;

        // Print the bytes to replace (pad right side), follwed by a space.
        int bytes_in_line = min_int(length, sizeof(bin_buf));

        for (int i = 0; i < bytes_in_line; i++)
            fprintf(file_out, "%02x", orig_buf[i]);
        for (int i = bytes_in_line; i < sizeof(orig_buf); i++)
            fputs("  ", file_out);

        fputc(',', file_out);

        // Print the bytes to replace with (also pad right side).
        for (int i = 0; i < bytes_in_line; i++)
            fprintf(file_out, "%02x", bin_buf[i]);
        for (int i = bytes_in_line; i < sizeof(bin_buf); i++)
            fputs("  ", file_out);

        // Done!
        fputc('\n', file_out);
    }

error_quit:
    if (section.data)
        free(section.data);
    return rval;
}

// --------------------------------------------------------------------------------------------------------------------

bool process_dfr_action(dfr_action_t *action, FILE *orig_file, FILE *dfr_file_out, const char *dfr_in_line) {
    bool rval = true;

    // Get the .ELF file.
    FILE *elf_file;
    if (action->elf_filename != nullptr && action->elf_filename[0] != '\0') {
        char elf_filename_buf[1024];
        const char *elf_filename = action->elf_filename;
        if (g_elfBasePath != nullptr && *g_elfBasePath != '\0') {
            snprintf(elf_filename_buf, sizeof(elf_filename_buf), "%s/%s", g_elfBasePath, action->elf_filename);
            elf_filename = elf_filename_buf;
        }

        if ((elf_file = fopen(elf_filename, "rb")) == nullptr) {
            char buf[2048];
            snprintf(buf, sizeof(buf), "%s: couldn't open .ELF file '%s'", dfr_in_line, elf_filename);
            perror(buf);
            rval = false;
            goto error_quit;
        }
    }
    else
        elf_file = nullptr;

    // Get our reading in position.
    if (orig_file)
        fseek(orig_file, action->offset, SEEK_SET);

    // Print the patch.
    if (!print_new_dfr_patch(action, orig_file, elf_file, dfr_file_out, dfr_in_line)) {
        rval = false;
        goto error_quit;
    }

error_quit:
    // We're done with the .ELF file.
    CLOSE_AND_RESET(elf_file);
    return rval;
}

// --------------------------------------------------------------------------------------------------------------------

bool process_dfr_in(FILE *orig_file, FILE *dfr_file_in, FILE *dfr_file_out) {
    char line_buf[65536];
    while (true) {
        fgets(line_buf, sizeof(line_buf), dfr_file_in);
        if (feof(dfr_file_in))
            break;

        bool skip_line = false;

        // Look for lines to create actions from.
        char stripped_line_buf[65536];
        snprintf(stripped_line_buf, sizeof(stripped_line_buf), "%s", line_buf);
        char *stripped_line = remove_whitespace(stripped_line_buf);
        auto const end_pos = strlen(stripped_line) - 1;

        if (end_pos > 0 && *stripped_line == '{' && stripped_line[end_pos] == '}') {
            skip_line = true;
            dfr_action_t action = {};
            stripped_line[end_pos] = '\0';
            stripped_line = remove_whitespace(stripped_line + 1);

            if (!dfr_action_init(&action, stripped_line))
                return false;
            if (!process_dfr_action(&action, orig_file, dfr_file_out, stripped_line)) {
                dfr_action_deinit(&action);
                return false;
            }
            dfr_action_deinit(&action);
        }

        if (!skip_line)
            fputs(line_buf, dfr_file_out);
    }

    return true;
}

// --------------------------------------------------------------------------------------------------------------------

int main(int argc, char **argv) {
    FILE *orig_file    = nullptr;
    FILE *dfr_file_in  = nullptr;

    int rval = 0;

    if (argc < 4) {
        fprintf(stderr,
            "usage: dfrc <orig-file> <dfr-in-file> <elf-dir>\n"
            "\n"
            "orig-file:    The original file on the disc (ex: /my_sf3_folder/X002.BIN)\n"
            "   An empty quoted string can be provided here to use all zeroes instead of actual content.\n"
            "\n"
            "dfr-in-file:  The base .DFR.in file to use. This will be modified and dumped to stdout.\n"
            "\n"
            "elf-dir:      Directory to locate .ELF files compiled into the resulting .DFR file\n"
            "\n"
        );
        return 1;
    }

    const char *orig_filename = argv[1];
    const char *dfr_filename  = argv[2];
    g_elfBasePath = argv[3];

    // Get the original file, if provided.
    if (orig_filename != nullptr && orig_filename[0] != '\0') {
        if ((orig_file = fopen(orig_filename, "r")) == nullptr) {
            char buf[256];
            snprintf(buf, sizeof(buf), "couldn't open original file '%s'", orig_filename);
            perror(buf);
            rval = 1;
            goto error_quit;
        }
    }

    // Get the .DFR.in file.
    if ((dfr_file_in = fopen(dfr_filename, "r")) == nullptr) {
        char buf[256];
        snprintf(buf, sizeof(buf), "couldn't open base .DFR.in file '%s'", dfr_filename);
        perror(buf);
        rval = 1;
        goto error_quit;
    }

    // Write the new .DFR file.
    if (!process_dfr_in(orig_file, dfr_file_in, stdout)) {
        rval = 1;
        goto error_quit;
    }
    fflush(stdout);

    // We're done with the input DFR file.
    CLOSE_AND_RESET(dfr_file_in);

error_quit:
    CLOSE_AND_RESET(orig_file);
    CLOSE_AND_RESET(dfr_file_in);

    return rval;
}
