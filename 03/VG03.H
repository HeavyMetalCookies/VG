

#include<stdlib.h> //:for: malloc(...)
#include<stdlib.h> //:for:   free(...)
#include <stdio.h> //:for: printf(...)

//:WC:Window Creation:
//:WCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWC://



//:WCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWC://



void VG03_Init(){
//|---- F01 ------|////[ DOTADIW:DLL_FUNC_LIST ]//
        F02_Init();  //[ DOTADIW:DLL_FUNC_LOAD ]//
//|-----F03 ------|////[ DOTADIW:DLL_CALL_CAST ]//
//|-----F04 ------|////[ DOTADIW:DLL_PARG_LIST ]//
//|-----F05 ------|////[ DOTADIW:DLL_WRAP_BOIL ]//
//|-----F06 ------|////[ DOTADIW:DLL_WRAP_MAKE ]//
//|-----F07 ------|////[ DOTADIW:MAKE_A_WINDOW ]//
    
}//[;]//

int
VG03_Demo( void ){

    printf("[BEG:VG03_DEMO]\n");

    VG03_Init();

    F07_Demo_SingleThreaded();

    printf("[END:VG03_DEMO]\n");

    return( 0 );
}//[;]//

struct VG03_BLUEPRINT{

    int( *Demo )( void );

}VG03={

    .Demo = &( VG03_Demo )

};//[struct]//



