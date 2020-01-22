//#FILE_REGION[ VG03.H ]BEG###################################//

int
VG03_Demo( void ){
    printf("[BEG:VG03_DEMO]\n");

///////////////////////////////. . . . . . 13
///////////////////////////////............|
///////////////////////////////123456789ABCD
    //:F01_Main(); //[ DOTADIW:DLL_FUNC_LIST ]//
    //:F02_Main(); //[ DOTADIW:DLL_FUNC_LOAD ]//
    //:F03_Main(); //[ DOTADIW:DLL_CALL_CAST ]//
    //:F04_Main(); //[ DOTADIW:DLL_STRUCTS   ]//
    //:F05_Main(); //[ DOTADIW:DLL_TYPEDEFS  ]//
    //:F06_Main(); //[ DOTADIW:DLL_PARG_LIST ]//
    //:F07_Main(); //[ DOTADIW:DLL_WRAP_BOIL ]//
    //:F08_Main(); //[ DOTADIW:DLL_WRAP_MAKE ]//

    //:F09_Main(); //[ DOTADIW:MAKE_A_WINDOW ]//
    //:F10_Main(); //[ DOTADIW:WIN_IN_THREAD ]//

    //:F20_Main(); //[ DOTADIW:VULKAN_STRUCT ]//
    //:F30_Main(); //[ DOTADIW:VULKAN_PFN_TD ]//
    //:F35_Main(); //[ DOTADIW:STRUCTS_W_PFN ]//

    //:F40_Main(); //[ DOTADIW:VK_INIT_PART1 ]//
    //:F50_Main(); //[ DOTADIW:VK_INST_FUNCS ]//
    //:F60_Main(); //[ DOTADIW:VK_INIT_PART2 ]//

    //:F61_Main(); //[ DOTADIW:WIN32_SURFACE ]//
    //:F62_Main(); //[ DOTADIW:PHYDEV_SELECT ]//
    //:F64_Main(); //[ DOTADIW:MAK_LOGIC_DEV ]//
    //:F66_Main(); //[ DOTADIW:RET_QUEUE_HAN ]//

    //:F70_Main(); //:CREATE_SWAPCHAIN       <<<<<<<<<<<<<<<<<<<<<< CrashOverTime?:NO
    //:F80_Main(); //:GET_SWAPCHAIN_IMAGES
    //:F90_Main(); //:GET_SWAPCHAIN_IMAGE_VIEWS
    //:F100_Main(); //:100 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< CrashOverTime?:NO

    F110_Main(); //:Form Absolute Path <<<<<<<<<<<<<<<<<<<<<<<<< CrashOverTime?:YES
    //:F120_Main(); //:Absolute path point to FINDER_FILE ? <<<<<<<<CrashOverTime?:YES
    //:F130_Main(); //:Extract .exe path from FINDER_FILE

    printf("[END:VG03_DEMO]\n");
    return( 0 );
}//[;]//

//:WHAT IS WHERE?
//[ F66_graphics_queue ]//

//[ F64_logical_device                  ]//
//[ F64_enabled_logical_device_features ]//

//[ F62_physical_device;                                     ]//
//[ F62_physical_device_features;                            ]//
//[ F62_physical_device_properties;                          ]//
//[                                                          ]//
//[ F62_qfp_graphics  ; //:qfp:queue_family_properties       ]//
//[ F62_qfp_compute   ;                                      ]//
//[ F62_qfp_graphics_and_compute_are_same_object;            ]//
//[                                                          ]//
//[ F62_qfi_graphics  ; //:qfi:queue_family_index            ]//
//[ F62_qfi_compute   ;                                      ]//

//[ F61_vulkan_surface                                       ]//

//[ f60_debug_utils_messenger                                ]//

//[ ... ]//

//#FILE_REGION[ VG03.H ]END###################################//