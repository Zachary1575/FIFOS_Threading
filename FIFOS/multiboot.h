
/* Copyright (C) 1999,2003,2007,2008,2009,2010  Free Software Foundation, Inc.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the &quot;Software&quot;), to
 *  deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL ANY
 *  DEVELOPER OR DISTRIBUTOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 *  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef MULTIBOOT_HEADER
#define MULTIBOOT_HEADER 1

/* <span class="roman">How many bytes from the start of the file we search for the header.</span> */
#define MULTIBOOT_SEARCH                        8192
#define MULTIBOOT_HEADER_ALIGN                  4

/* <span class="roman">The magic field should contain this.</span> */
#define MULTIBOOT_HEADER_MAGIC                  0x1BADB002

/* <span class="roman">This should be in %eax.</span> */
#define MULTIBOOT_BOOTLOADER_MAGIC              0x2BADB002

/* <span class="roman">Alignment of multiboot modules.</span> */
#define MULTIBOOT_MOD_ALIGN                     0x00001000

/* <span class="roman">Alignment of the multiboot info structure.</span> */
#define MULTIBOOT_INFO_ALIGN                    0x00000004

/* <span class="roman">Flags set in the &rsquo;flags&rsquo; member of the multiboot header.</span> */

/* <span class="roman">Align all boot modules on i386 page (4KB) boundaries.</span> */
#define MULTIBOOT_PAGE_ALIGN                    0x00000001

/* <span class="roman">Must pass memory information to OS.</span> */
#define MULTIBOOT_MEMORY_INFO                   0x00000002

/* <span class="roman">Must pass video information to OS.</span> */
#define MULTIBOOT_VIDEO_MODE                    0x00000004

/* <span class="roman">This flag indicates the use of the address fields in the header.</span> */
#define MULTIBOOT_AOUT_KLUDGE                   0x00010000

/* <span class="roman">Flags to be set in the &rsquo;flags&rsquo; member of the multiboot info structure.</span> */

/* <span class="roman">is there basic lower/upper memory information?</span> */
#define MULTIBOOT_INFO_MEMORY                   0x00000001
/* <span class="roman">is there a boot device set?</span> */
#define MULTIBOOT_INFO_BOOTDEV                  0x00000002
/* <span class="roman">is the command-line defined?</span> */
#define MULTIBOOT_INFO_CMDLINE                  0x00000004
/* <span class="roman">are there modules to do something with?</span> */
#define MULTIBOOT_INFO_MODS                     0x00000008

/* <span class="roman">These next two are mutually exclusive</span> */

/* <span class="roman">is there a symbol table loaded?</span> */
#define MULTIBOOT_INFO_AOUT_SYMS                0x00000010
/* <span class="roman">is there an ELF section header table?</span> */
#define MULTIBOOT_INFO_ELF_SHDR                 0X00000020

/* <span class="roman">is there a full memory map?</span> */
#define MULTIBOOT_INFO_MEM_MAP                  0x00000040

/* <span class="roman">Is there drive info?</span> */
#define MULTIBOOT_INFO_DRIVE_INFO               0x00000080

/* <span class="roman">Is there a config table?</span> */
#define MULTIBOOT_INFO_CONFIG_TABLE             0x00000100

/* <span class="roman">Is there a boot loader name?</span> */
#define MULTIBOOT_INFO_BOOT_LOADER_NAME         0x00000200

/* <span class="roman">Is there a APM table?</span> */
#define MULTIBOOT_INFO_APM_TABLE                0x00000400

/* <span class="roman">Is there video information?</span> */
#define MULTIBOOT_INFO_VBE_INFO                 0x00000800
#define MULTIBOOT_INFO_FRAMEBUFFER_INFO         0x00001000

#ifndef ASM_FILE

typedef unsigned char           multiboot_uint8_t;
typedef unsigned short          multiboot_uint16_t;
typedef unsigned int            multiboot_uint32_t;
typedef unsigned long long      multiboot_uint64_t;

struct multiboot_header
{
  /* <span class="roman">Must be MULTIBOOT_MAGIC - see above.</span> */
  multiboot_uint32_t magic;

  /* <span class="roman">Feature flags.</span> */
  multiboot_uint32_t flags;

  /* <span class="roman">The above fields plus this one must equal 0 mod 2^32.</span> */
  multiboot_uint32_t checksum;

  /* <span class="roman">These are only valid if MULTIBOOT_AOUT_KLUDGE is set.</span> */
  multiboot_uint32_t header_addr;
  multiboot_uint32_t load_addr;
  multiboot_uint32_t load_end_addr;
  multiboot_uint32_t bss_end_addr;
  multiboot_uint32_t entry_addr;

  /* <span class="roman">These are only valid if MULTIBOOT_VIDEO_MODE is set.</span> */
  multiboot_uint32_t mode_type;
  multiboot_uint32_t width;
  multiboot_uint32_t height;
  multiboot_uint32_t depth;
};

/* <span class="roman">The symbol table for a.out.</span> */
struct multiboot_aout_symbol_table
{
  multiboot_uint32_t tabsize;
  multiboot_uint32_t strsize;
  multiboot_uint32_t addr;
  multiboot_uint32_t reserved;
};
typedef struct multiboot_aout_symbol_table multiboot_aout_symbol_table_t;

/* <span class="roman">The section header table for ELF.</span> */
struct multiboot_elf_section_header_table
{
  multiboot_uint32_t num;
  multiboot_uint32_t size;
  multiboot_uint32_t addr;
  multiboot_uint32_t shndx;
};
typedef struct multiboot_elf_section_header_table multiboot_elf_section_header_table_t;

struct multiboot_info
{
  /* <span class="roman">Multiboot info version number</span> */
  multiboot_uint32_t flags;

  /* <span class="roman">Available memory from BIOS</span> */
  multiboot_uint32_t mem_lower;
  multiboot_uint32_t mem_upper;

  /* <span class="roman">&quot;root&quot; partition</span> */
  multiboot_uint32_t boot_device;

  /* <span class="roman">Kernel command line</span> */
  multiboot_uint32_t cmdline;

  /* <span class="roman">Boot-Module list</span> */
  multiboot_uint32_t mods_count;
  multiboot_uint32_t mods_addr;

  union
  {
    multiboot_aout_symbol_table_t aout_sym;
    multiboot_elf_section_header_table_t elf_sec;
  } u;

  /* <span class="roman">Memory Mapping buffer</span> */
  multiboot_uint32_t mmap_length;
  multiboot_uint32_t mmap_addr;

  /* <span class="roman">Drive Info buffer</span> */
  multiboot_uint32_t drives_length;
  multiboot_uint32_t drives_addr;

  /* <span class="roman">ROM configuration table</span> */
  multiboot_uint32_t config_table;

  /* <span class="roman">Boot Loader Name</span> */
  multiboot_uint32_t boot_loader_name;

  /* APM table */
  multiboot_uint32_t apm_table;

  /* <span class="roman">Video</span> */
  multiboot_uint32_t vbe_control_info;
  multiboot_uint32_t vbe_mode_info;
  multiboot_uint16_t vbe_mode;
  multiboot_uint16_t vbe_interface_seg;
  multiboot_uint16_t vbe_interface_off;
  multiboot_uint16_t vbe_interface_len;

  multiboot_uint64_t framebuffer_addr;
  multiboot_uint32_t framebuffer_pitch;
  multiboot_uint32_t framebuffer_width;
  multiboot_uint32_t framebuffer_height;
  multiboot_uint8_t framebuffer_bpp;
#define MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED 0
#define MULTIBOOT_FRAMEBUFFER_TYPE_RGB     1
#define MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT     2
  multiboot_uint8_t framebuffer_type;
  union
  {
    struct
    {
      multiboot_uint32_t framebuffer_palette_addr;
      multiboot_uint16_t framebuffer_palette_num_colors;
    };
    struct
    {
      multiboot_uint8_t framebuffer_red_field_position;
      multiboot_uint8_t framebuffer_red_mask_size;
      multiboot_uint8_t framebuffer_green_field_position;
      multiboot_uint8_t framebuffer_green_mask_size;
      multiboot_uint8_t framebuffer_blue_field_position;
      multiboot_uint8_t framebuffer_blue_mask_size;
    };
  };
};
typedef struct multiboot_info multiboot_info_t;

struct multiboot_color
{
  multiboot_uint8_t red;
  multiboot_uint8_t green;
  multiboot_uint8_t blue;
};

struct multiboot_mmap_entry
{
  multiboot_uint32_t size;
  multiboot_uint64_t addr;
  multiboot_uint64_t len;
#define MULTIBOOT_MEMORY_AVAILABLE              1
#define MULTIBOOT_MEMORY_RESERVED               2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE       3
#define MULTIBOOT_MEMORY_NVS                    4
#define MULTIBOOT_MEMORY_BADRAM                 5
  multiboot_uint32_t type;
} __attribute__((packed));
typedef struct multiboot_mmap_entry multiboot_memory_map_t;

struct multiboot_mod_list
{
  /* <span class="roman">the memory used goes from bytes &rsquo;mod_start&rsquo; to &rsquo;mod_end-1&rsquo; inclusive</span> */
  multiboot_uint32_t mod_start;
  multiboot_uint32_t mod_end;

  /* <span class="roman">Module command line</span> */
  multiboot_uint32_t cmdline;

  /*padding to take it to 16 bytes (must be zero)*/
  multiboot_uint32_t pad;
};
typedef struct multiboot_mod_list multiboot_module_t;

/* <span class="roman">APM BIOS info.</span> */
struct multiboot_apm_info
{
  multiboot_uint16_t version;
  multiboot_uint16_t cseg;
  multiboot_uint32_t offset;
  multiboot_uint16_t cseg_16;
  multiboot_uint16_t dseg;
  multiboot_uint16_t flags;
  multiboot_uint16_t cseg_len;
  multiboot_uint16_t cseg_16_len;
  multiboot_uint16_t dseg_len;
};

#endif /*!ASM_FILE */

#endif /*!MULTIBOOT_HEADER */
 
