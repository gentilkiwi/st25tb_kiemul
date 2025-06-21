/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "cli_dump.h"
#include "cli_data.h"
#include "cli_slot.h"
#if defined(REFERENCES_DATA_READY)
#include "cli_ref.h"
#endif
#include "cli_card.h"

const CLI_FUNCTION CLI_DUMP_Functions[] = {
    {.name = "info",    .function = CLI_DUMP_info,      .description = "Dump generic informations from data, slots and references"},
    {.name = "data",    .function = CLI_DATA_dump,      .description = "> data dump"},
    {.name = "slot",    .function = CLI_SLOT_dump,      .description = "> slot dump"},
#if defined(REFERENCES_DATA_READY)
    {.name = "ref",     .function = CLI_REF_dump,       .description = "> ref dump"},
#endif
    {.name = "card",    .function = CLI_CARD_dump,      .description = "> card dump"},
};

const CLI_MODULE CLI_DUMP_Module = {.name = "dump", .description = "Helper with global informations and to remote functions", .nbFunctions = count_of(CLI_DUMP_Functions), .Functions = CLI_DUMP_Functions};

void CLI_DUMP_info()
{
    CLI_DATA_info();
    CLI_SLOT_info();
#if defined(REFERENCES_DATA_READY)
    CLI_REF_info();
#endif
}
