#include <stdint.h>
#include <diag/Trace.h>
#include "bit.h"
#include "Bit_Mask.h"
#include "Error_codes.h"
#include "App.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

typedef struct {
	uint32_t startOfValidRange;
	uint32_t endOfValidRange;
	uint32_t startOfInvalidRange;
	uint32_t endOfInvalidRange;
}test_t ;




int
main(int argc, char* argv[])
{
	App_Init();

  while (1)
    {
	  App_main();
    }
}


#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
