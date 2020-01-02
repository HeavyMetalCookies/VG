//#FILE_REGION[ VG03.H ]BEG###################################//
/////////////////////////////////. . . . . . 13
/////////////////////////////////............|
/////////////////////////////////123456789ABCD
//|---- F01 ------|////[ DOTADIW:DLL_FUNC_LIST ]//
//|---- F02 ------|////[ DOTADIW:DLL_FUNC_LOAD ]//
//|-----F03 ------|////[ DOTADIW:DLL_CALL_CAST ]//

//|-----F04 ------|////[ DOTADIW:DLL_STRUCTS   ]//
//|-----F05 ------|////[ DOTADIW:DLL_TYPEDEFS  ]//

//|-----F06 ------|////[ DOTADIW:DLL_PARG_LIST ]//
//|-----F07 ------|////[ DOTADIW:DLL_WRAP_BOIL ]//
//|-----F08 ------|////[ DOTADIW:DLL_WRAP_MAKE ]//

//|-----F09 ------|////[ DOTADIW:MAKE_A_WINDOW ]//
//|-----F10 ------|////[ DOTADIW:WIN_IN_THREAD ]//

//|-----F20 ------|////[ DOTADIW:VULKAN_STRUCT ]//
//|-----F30 ------|////[ DOTADIW:VULKAN_PFN_TD ]//
//|-----F35 ------|////[ DOTADIW:STRUCTS_W_PFN ]//

//|-----F40 ------|////[ DOTADIW:VK_INIT_PART1 ]//
//|-----F50 ------|////[ DOTADIW:VK_INST_FUNCS ]//
//|-----F60 ------|////[ DOTADIW:VK_INIT_PART2 ]//

//|-----F61 ------|////[ DOTADIW:WIN32_SURFACE ]//
//|-----F62 ------|////[ DOTADIW:PHYDEV_SELECT ]//
//|-----F64 ------|////[ DOTADIW:MAK_LOGIC_DEV ]//
//|-----F66 ------|////[ DOTADIW:RET_QUEUE_HAN ]//
    

int
VG03_Demo( void ){
    printf("[BEG:VG03_DEMO]\n");


    //:F10_Main();
    //:F35_Main();
    //:F40_Main();
    //:F50_Main();
    //:F60_Main();
    //:F61_Main();
    //:F62_Main();
    //:F64_Main();
       F66_Main();

    // F70_Main();


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