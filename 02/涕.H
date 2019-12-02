
//:Include Vulkan:
#include "V:/VK_HEAD/include/vulkan/vulkan.h" 

#include <stdio.h> //:for: printf(...)

struct 涕{
    //:IDEA: Try to keep as coarse grain as
    //:      possible. Subdivide later if needed.
    
    int unused;

    struct USER32{
        void* DefWindowProcW; //:#LAZY_VOID#://
    }USER32;

}涕={ 0 };


void 涕_LoadDLLFunc_DefWindowProcW( void ){
    
}

new-windowproc
new-win32-window-proc
new-win32win-proc
new-win32winproc
new-windows-windowproc

__int64 __stdcall 
涕_WindowProc(
/**/     void*              hwnd
/**/     unsigned    int    uMsg
/**/     unsigned  __int64  wParam
/**/               __int64  lParam
){
    if(0 >= 涕.USER32->DefWindowProcW){
        涕_LoadDLLFunc_DefWindowProcW();
    };;

    switch(uMsg){ //:- - - - - - - - - - - - - -://
    case WM_SIZE:{

        printf("[GLEB_SWIN:WM_SIZE]\n");
        fflush(stdout);

        ENGETHER.THREADING.InterlockedIncrement64(
            &( GLEB_SWIN.THREAD_SAFE_FLAGS.
               resize_message_count )
        );;

        //: #define C_B GLEB_SWIN.OPTIONAL_CALLBACKS
        //: if(C_B.resize_function_has){
        //:    C_B.resize_function();
        //: };;
        //: #undef  C_B

        //# [TODO]: #// InterlockedExchangeAddAcquire64( THREAD_SAFE_FLAGS.resize_message_count, 1 );

    }break;
    case WM_KEYDOWN:{
        if(wParam==VK_ESCAPE){

            ok = 涕->USER32.DestroyWindow(hwnd);
            if(0==ok){gleb_swin_Halt("[0OK_1]");}

        }else{
            KEBO_DOWN_HandleVirtualKey( wParam );
        };;

    }break;

    case WM_KEYUP:{
        
            KEBO_UPPP_HandleVirtualKey( wParam );

    }break;

    //:WM_CLOSE: The "[X]" button was clicked.
    case WM_CLOSE:
        ok = 涕->USER32.DestroyWindow(hwnd); 
        if(0==ok){gleb_swin_Halt("[0OK_2]");}

    //:WM_DESTROY: ( DESTROYED|DESTROYING )
    case WM_DESTROY:  
        //: Send "WM_QUIT" to exit uMsg loop.
        涕->USER32.PostQuitMessage(0);

    case WM_PAINT:
        
        //:Be carefull about buffer swap here.
        //:If OpenGL, the bufferswap call
        //:needs to be done from whatever
        //:thread OpenGL is running on.

    //:Keep window responsive:
    default: 
        return_this_result=(
            涕->USER32.DefWindowProcW(
                Hw,uMsg,wParam,lParam
            )
        );;
    };;//:- - - - - - - - - - - - - - - - - - -://

    return( return_this_result );

}

int 涕_CreateWindow(){

    #define T struct tagWNDCLASSEXW //////////////
    T* t = malloc(sizeof( T ) );
    ;;/*01*/t->cbSize        =( 

        sizeof( T )

    );/*02*/t->style         =( 
    /**/ ( 0
    /**/   |
    /**/     (   //:WS_OVERLAPPED_WINDOW
    /**/         0
    /**/         |  0x00000000L //: WS_OVERLAPPED 
    /**/         |  0x00C00000L //: WS_CAPTION  
    /**/         |  0x00080000L //: WS_SYSMENU 
    /**/         |  0x00040000L //: WS_THICKFRAME 
    /**/         |  0x00020000L //: WS_MINIMIZEBOX 
    /**/         |  0x00010000L //: WS_MAXIMIZEBOX
    /**/         | 
    /**/         0
    /**/     ) 
    /**/   |
    /**/     //:CS_OWNDC    
    /**/     0x0020
    /**/ 
    /**/   |
    /**/   0
    /**/ )
    );/*03*/t->lpfnWndProc   =( 

        &( 涕_WindowProc )

    );/*04*/t->cbClsExtra    =( 

    );/*05*/t->cbWndExtra    =( 

    );/*06*/t->hInstance     =( 

    );/*07*/t->hIcon         =( 

    );/*08*/t->hCursor       =( 

    );/*09*/t->hbrBackground =( 

    );/*10*/t->lpszMenuName  =( 

    );/*11*/t->lpszClassName =( 

    );/*12*/t->hIconSm       =( 

    );
    undef T //////////////////////////////////////

}

int 涕_Demo(){
    printf("[涕_Demo()...]\n");
    return( 0 );
}



//|////////////////////////////////////////////|//
//|     -///-                        -///-     |//
//|....(( 0 ))|| ||_ _--  --_ _|| ||(( 0 ))....|//
//|_  __      __  __  __  __  __  __      __  _|//
//| \/  \    /  \/  \/  \/  \/  \/  \    /  \/ |//
//|      \  /                        \  /      |//
//|       \/                          \/       |//
//+ BEG: #BOTTOM_OF_FILE_COMMENTS_SECTION#     +//
//|           /\                  /\           |//
//|          /  \                /  \          |//
//|_--__--__/    \__/\__/\__/\__/    \__--__--_|//
//|                                            |//
//|       ______________________________       |//
//|______/                              \______|//
#if(BOTTOM_OF_FILE_COMMENTS_SECTION) /////////////
/** ****************************************** |||
                                                   
#LAZY_VOID#
    I was lazy, so I made the type a void*
    instead of it's actual type. Because
    it's actual literal type is too complex.
                                                   
||| ****************************************** **/ 
#endif ///////////////////////////////////////////
//|______                                ______|//
//|||||||\______________________________/|||||||//
//|                                            |//
//|....(( 0 ))|| ||_ _--  --_ _|| ||(( 0 ))....|//
//|_  __      __  __  __  __  __  __      __  _|//
//| \/  \    /  \/  \/  \/  \/  \/  \    /  \/ |//
//|      \  /                        \  /      |//
//|       \/                          \/       |//
//+ END: #BOTTOM_OF_FILE_COMMENTS_SECTION#     +//
//|           /\                  /\           |//
//|          /  \                /  \          |//
//|_--__--__/    \__/\__/\__/\__/    \__--__--_|//
//|                                            |//
//|____________________________________________|//
