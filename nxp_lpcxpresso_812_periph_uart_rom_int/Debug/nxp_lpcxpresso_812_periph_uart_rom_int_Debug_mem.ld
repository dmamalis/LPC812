/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-2014
 * (c) NXP Semiconductors 2013-2014
 * Linker script memory definitions
 * Created from LinkMemoryTemplate
 * By LPCXpresso v7.3.0 [Build 186] [2014-07-09]  on Wed Jul 23 11:20:40 CEST 2014)
*/

MEMORY
{
  /* Define each memory region */
  MFlash16 (rx) : ORIGIN = 0x0, LENGTH = 0x4000 /* 16K bytes */
  RamLoc4 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x1000 /* 4K bytes */


}
  /* Define a symbol for the top of each memory region */
  __top_MFlash16 = 0x0 + 0x4000;
  __top_RamLoc4 = 0x10000000 + 0x1000;



