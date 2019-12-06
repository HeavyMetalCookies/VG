//[ DLLL: DLLL_Loader                          ]//
//+--------------------------------------------+//
//| PUBLIC:                                    |//
//| DLLL_FUNC                                  |//
//| DLLL_DLIB                                  |//
//| DLLL_WRAP_LoadLibraryA                     |//
//| DLLL_WRAP_GetProcAddress                   |//
//+--------------------------------------------+//



//| Only choose one to set to 1 |//
#define COMPILE_FOR_windows_10_64bit 1

//: typedef 
//:     void (*DLLL_GENERIC_FUNCTION_POINTER)
//:     ( void ); //:<<"void" may need to be omitted.




#if( COMPILE_FOR_windows_10_64bit >= 1 )

    #include "./TARG/WIN10_x64._"

    typedef
        TYPEDEF_HMODULE
        DLLL_DLIB;

    typedef 
        TYPEDEF_FARPROC 
        DLLL_FUNC;

#endif


static unsigned char
dll_init_already_called =((( 0 )));
void
DLLL_Init(){

    if( dll_init_already_called>0){ return; };

    TYPEDEF_HMODULE 
    hKernel32 =(
    /**/    JMIM_GetModuleBaseAddress(
    /**/        L"KERNEL32.DLL"
    /**/    )
    );;

    LoadLibraryAF 
    pLoadLibraryA =(
    /**/    (LoadLibraryAF)
    /**/    JMIM_GetExportAddress(
    /**/        hKernel32
    /**/    ,  "LoadLibraryA"
    /**/    )
    );;

    GetProcAddressF 
    pGetProcAddress =(
    /**/    (GetProcAddressF)
    /**/    JMIM_GetExportAddress(
    /**/        hKernel32
    /**/    ,   "GetProcAddress"
    /**/    )
    );;

    //:Assign the private function pointers
    //:defined in the specific operating system
    //:implementation files:
    dll_LoadLibraryA   =pLoadLibraryA  ;
    dll_GetProcAddress =pGetProcAddress;

    dll_init_already_called=( 1 );
    
}//[;]//

DLLL_DLIB
DLLL_WRAP_LoadLibraryA(
    const char* name
){
    if(NULL==dll_LoadLibraryA){
        printf("[FORGOT:DLLL_Init()?](LLA)\n");
        assert(NULL!=dll_LoadLibraryA);
    };;

    //:Implementation_Specific:
    return( dll_LoadLibraryA( name ) );
}//[;]//

DLLL_FUNC
DLLL_WRAP_GetProcAddress(
    DLLL_DLIB   dlib
,   const char* name
){
    if(NULL==dll_GetProcAddress){
        printf("[FORGOT:DLLL_Init()?](GPA)\n");
        assert(NULL!=dll_GetProcAddress);
    };;

    //:Implementation_Specific:
    DLLL_FUNC ret;
    ret = (DLLL_FUNC)
           dll_GetProcAddress(dlib, name);
    return(  ret  );
}//[;]//

//////////////////////////////////////////////////
//|  Let's be real... You are not going to     |//
//|  remember "DLLL_WRAP_*" Better just stick  |//
//|  with habits that are less complex.        |//
//+--------------------------------------------+//               
//|  Also,prioritize ease of use! Not speed    |//
//|  here.                                     |//
//////////////////////////////////////////////////

DLLL_DLIB
DLLL_LoadLibraryA(
    const char* name
){
    DLLL_Init(); //:LazyInit

    DLLL_DLIB ret=(
    /**/    DLLL_WRAP_LoadLibraryA(
    /**/        name
    /**/    )
    );;

    return( ret );

}//[;]//

DLLL_FUNC
DLLL_GetProcAddress(
    DLLL_DLIB   dlib
,   const char* name
){
    DLLL_Init(); //:LazyInit

    DLLL_FUNC ret=(
    /**/    DLLL_WRAP_GetProcAddress(
    /**/        dlib
    /**/    ,   name
    /**/    )
    );;

    return( ret );

}//[;]//


//////////////////////////////////////////////////
