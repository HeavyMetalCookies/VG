
//:Trashing this because:
//:It brings in too many dependencies.
//:Just do it over again. And learn.

//: #include "../KEBO/KEBO.H" //:Keyboard Handler

//|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|//
//|PUBLIC Functions:                           |//
//|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _   |//
int   MAKEWIND_Demo(          void );      //||//
int   MAKEWIND_Demonstration( void );      //||//
                                            //||//
void  MAKEWIND_Init(       /**void**/  );  //||//
void  MAKEWIND_Initialize( /**void**/  );  //||//
                                            //||//
void* MAKEWIND_GetWindowDeviceContext();   //||//
void* MAKEWIND_GetWinDC();                 //||//
                                            //||//
void  MAKEWIND_Wait(         /**void**/  );//||//
void  MAKEWIND_WaitForUserToCloseWindow( );//||//
                                            //||//
int   MAKEWIND_IsWindowStillOpen( );       //||//
                                            //||//
//| So we don't have to return "RECT"       //||//
//| Structures, use 4 calls instead of      //||//
//| making "MAKEWIND_GetClientArea"        //||//
int   MAKEWIND_GetClient_X(  );            //||//
int   MAKEWIND_GetClient_Y(  );            //||//
int   MAKEWIND_GetClient_WID();            //||//
int   MAKEWIND_GetClient_HIG();            //||//
                                            //||//
void  MAKEWIND_PutRenderTickFunction(
    void(*function_name)( void )
);

void  MAKEWIND_SwapBuffers( void );
//|____________________________________________|//

//:KEY/PREFIXES:
//:    makewind_:
//:    The namespace prefix for all functions
//:    that belong to this section of code.
//:
//:    gleb: open_GL_Easy_Bindings
//:    
//:    swin:
//:    SWIN=="SILKWIN"==="THREADED_WINDOW"
//:    The idea is a "window made of silk" 
//:    because threads can be made of silk.
//:    I am thinking the window was woven
//:    by a spider's threads.
//:
//:    pfn: Pointer_to_FuNction
//:         (Convention take from Vulkan)
//:
//:CONVENTIONS:
//:
//:  1. Non-terminal objects of library
//:     structs are ALL_CAPITAL.
//:
//:  2. Terminal objects of library struct are:
//:     A: CamelCaseIfFunction
//:     B: snake_case_if_variable
//:     C: OR: Written in convention of whatever
//:        I am trying to wrap that exists from
//:        some other library I don't own.
//:
//:  3. Includes often are put near where
//:     they are needed, rather than all at
//:     the top of the file. Standard headers
//:     have include gaurds, so this shouldn't
//:     be a problem.
//:
//:  4. Global Windows Functions Allowed:
//:     1. LoadLibraryA
//:     2. GetProcAddress
//:     Anything else should be wrapped in
//:     a library struct that tells us the
//:     .dll file of origin.
//:
//:     Convoluted and rigid and a pain to
//:     port to another operating system?
//:
//:     I'll worry about porting after I've made
//:     a million dollars off of something.
//:     Otherwise, not worth the hassel.


int MAKEWIND_show_okay_message = 1;


#include <stdio.h> //:printf(...)
void
makewind_OK( const char* ok_message ){

    if( MAKEWIND_show_okay_message ){

        printf(
            "[MAKEWIND:OK]:%s\n"
        ,  ok_message 
        );;

    };;
} //[makewind_OK]//



#include <stdio.h> //:printf(...)
#include <stdio.h> //:fflush(stdout)
#include <Windows.h> //:for: GetProcAddress
#include <stdint.h> //: uintptr_t




//:Typedefs for MY types:
//:TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT://
 
//:¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯://
//:                                            ://
//:  Attempt to do the following with          ://
//:  windows's platform types:                 ://
//:                                            ://
//:  1. Reduce mental indirection.             ://
//:  2. Quickly deduce size of types.          ://
//:                                            ://
//:  Microsoft hungarian notation is kind of   ://
//:  like a hungarian notation that could not  ://
//:  decide if it was apps hungarian or        ://
//:  systems hungarian. Usually I am fan of    ://
//:  APPS hungarian ant NOT a fan of           ://
//:  systems hungarian. But because of all     ://
//:  the indirection with microsoft types,     ://
//:  I will add my own SYSTEMS hungarian       ://
//:  notation to the types. The variable       ://
//:  names can use APPS hungarian if I need    ://
//:  it.                                       ://
//:                                            ://
//:-  --  --  --  --  --  --  --  --  --  --  -://
//:typedef unsigned long DWORD;
//:typedef unsigned int UINT;

//:Prefix at beginning of type:
//:----------------------------------://
//:p_: pointer type                  ://
//:v_: pointer to void.              ://
//:f_: pointer to function.          ://
//:c_: pointer to character          ://
//:s_: pointer to struct (or class)  ://
//:u_: pointer to unsigned integer   ://
//:i_: pointer to signed integer.    ://
//:----------------------------------://

//: i##:
//: i08: integer (signed   ) 08 bits.
//: i16: integer (signed   ) 16 bits.
//: i32: integer (signed   ) 32 bits.
//: i64: integer (signed   ) 64 bits.

//: u##:
//: u08: integer (UN-signed) 08 bits.
//: u16: integer (UN-signed) 16 bits.
//: u32: integer (UN-signed) 32 bits.
//: u64: integer (UN-signed) 64 bits.

//: b##:
//: b08: class, struct, any char type: 08 bits.
//: b16: class, struct, any char type: 16 bits.
//: b32: class, struct, any char type: 32 bits.
//: b64: class, struct, any char type: 64 bits.

//: #B:
//: 1B: 1 BYTES
//: 2B: 2 BYTES
//: 4B: 4 BYTES
//: 8B: 8 BYTES

typedef  int32_t              BOOL_i32_4B   ;
typedef  unsigned  long int  DWORD_u32_4B   ;
typedef  uint32_t             UINT_u32_4B   ;
typedef  unsigned   short     WORD_u16_2B   ;
typedef  unsigned   short     ATOM_u16_2B   ;
typedef             char      CHAR_b08_1B   ;
typedef  unsigned __int64   SIZE_T_u64_8B   ;
typedef           __int64  LRESULT_i64_8B   ;
typedef  unsigned __int64   WPARAM_u64_8B   ;
typedef           __int64   LPARAM_i64_8B   ;
//:

//:pointers to character: (c_)
//:--------------------------------------------://
typedef const    char*    c_LPCSTR_b08_1B   ;  
typedef const wchar_t*   c_LPCWSTR_b16_2B   ;
//:--------------------------------------------://

//:pointers to void: (v_)
//:--------------------------------------------://
typedef              void* v_HANDLE   ;
typedef              void* v_HMODULE  ;   
typedef              void* v_HINSTANCE;
typedef struct  HGDIOBJ__* v_HGDIOBJ  ;
typedef struct     HWND__* v_HWND     ;
typedef struct    HICON__* v_HICON    ;
typedef struct    HMENU__* v_HMENU    ;
typedef struct   HBRUSH__* v_HBRUSH   ;
//:Not a mistake. windef.h says:
//:typedef HICON HCURSOR;
typedef struct HICON__* v_HCURSOR;
typedef           void* v_LPVOID;
//:--------------------------------------------://

typedef struct tagMSG  MSG_48B;
typedef 
    struct   _SECURITY_ATTRIBUTES  
    *s_LPSECURITY_ATTRIBUTES;

typedef  struct tagRECT*  s_RECT;

//: You cannot use void* as a generic function
//: pointer so windows has "FARPROC".
//: We point to intptr_t, a signed integer
//: that is large enough to hold a pointer.
typedef intptr_t (__stdcall *f_FARPROC) ( void );

typedef 
    LRESULT_i64_8B
    (__stdcall *f_WNDPROC)(
        v_HWND
    ,   UINT_u32_4B
    ,   WPARAM_u64_8B
    ,   LPARAM_i64_8B
    );

//: This struct should be a byte-for-byte
//: re-creation of the windows
//: WNDCLASSEXW struct. On my 64bit
//: system, sizeof(WNDCLASSEXW) is
//: 80 bytes.
//: I've decided NOT to support 32bit.
typedef struct makewind_tagWNDCLASSEXW {
        UINT_u32_4B  cbSize       ;
        UINT_u32_4B  style        ;
          f_WNDPROC  lpfnWndProc  ;
                int  cbClsExtra   ;
                int  cbWndExtra   ;
        v_HINSTANCE  hInstance    ;
            v_HICON  hIcon        ;
          v_HCURSOR  hCursor      ;
           v_HBRUSH  hbrBackground;
   c_LPCWSTR_b16_2B  lpszMenuName ;
   c_LPCWSTR_b16_2B  lpszClassName;
            v_HICON  hIconSm      ;
} makewind_WNDCLASSEXW;

//: Windows Coding Conventions Say,
//: The following are always the size of
//: a pointer. 32bit on 32 bit windows.
//: 64bit on 64bit windows.
//: DWORD_PTR
//: INT_PTR
//: LONG_PTR
//: ULONG_PTR
//: UINT_PTR
//:
//: So the original hungarian notation was
//: apps hungarian?
//: BEG:QUOTE:
//: In its original form, Hungarian notation 
//: gives semantic information about a variable
//: END:QUOTE:
//:____________________________________________://

void
makewind_AssertCorrectSizesOfTypes(){

    int size_errors=0;
    int wrong_sign =0;

    
    if(sizeof(   BOOL_i32_4B) != 4 ){
        printf("[BOOL_i32_4B]");
        size_errors++;
    };;
    if(sizeof(  DWORD_u32_4B) != 4 ){
        printf("[DWORD_u32_4B]");
        size_errors++;
    };;
    if(sizeof(   UINT_u32_4B) != 4 ){
        printf("[UINT_u32_4B]");
        size_errors++;
    };;
    if(sizeof(   WORD_u16_2B) != 2 ){
        printf("[WORD_u16_2B]");
        size_errors++;
    };;
    //:I recall windows returning negative
    //:characters to flag status codes or
    //:something. So pretty sure CHAR
    //:is a signed type.
    if(sizeof(   CHAR_b08_1B) != 1 ){
        printf("[CHAR_b08_1B]");
        size_errors++;
    };;
    {
        //:assume if this works, c_LPCSTR_b08_1B
        //:is correctly defined.
        //:"i08_1B" refers to size of 
        //:POINTED TO type, not the size of
        //:the pointer.
        const char pointed_to_value = 'e';
        c_LPCSTR_b08_1B pointer = &(
            pointed_to_value
        );;
        if( *pointer == 'e' ){
            //:okay
        }else{
            printf("[WTF]");
        };;
    }

    //////////////////////////////////////////////
    ;{
         BOOL_i32_4B v =(
        (BOOL_i32_4B)(-1) );;
        if( v >= 0 ){ 
            wrong_sign++;
            printf("[WS:BOOL_i32_4B]");
        }
    }{
         DWORD_u32_4B v =(
        (DWORD_u32_4B)(-1) );;
        if( v <= 0 ){ 
            wrong_sign++; 
            printf("[WS:DWORD_u32_4B]");
        }
    }{
         UINT_u32_4B v =(
        (UINT_u32_4B)(-1) );;
        if( v <= 0 ){ 
            wrong_sign++; 
            printf("[WS:UINT_u32_4B]");
        }
    }{
         WORD_u16_2B v =(
        (WORD_u16_2B)(-1) );;
        if( v <= 0 ){ 
            wrong_sign++; 
            printf("[WS:WORD_u16_2B]");
        }
    }{
         CHAR_b08_1B v =(
        (CHAR_b08_1B)(-1) );;
        if( v > 0 ){ 
            //:Turns out that character type
            //:signedness is compiler dependent,
            //:so... Dont test this.
            wrong_sign++; 
            printf("[WS:CHAR_b08_1B]");
        }
    };;

    //////////////////////////////////////////////

    if(wrong_sign  > 0){
        printf(
            "[TypesOfWrongSign]:%d\n"
        ,   wrong_sign
        );;
    };;
    if(size_errors > 0){
        printf("[MAKEWIND:AssertFailed]\n");
        printf(
            "[TypesNotCorrectBitWidth]:%d\n"
        ,   size_errors
        );;
    };;
    if( size_errors > 0 || wrong_sign > 0 ){
        printf("[MAKEWIND:AssertFailed]\n");
        fflush( stdout );
        exit( 666 );
    };;

} //[makewind_AssertCorrectSizesOfTypes]//
//:____________________________________________://


//:¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯://
//: Generic function pointer for library:      ://
//:                                            ://
//:     MAKEWIND                              ://
//:     (Sub Library Of "GLEB")                ://
//:     (The Window Wrangling Part)            ://
//:                                            ://
//: Used for strict compilation in C99 when    ://
//: casting result of "GetProcAddress"         ://
//: The "C Language" only guarantees           ://
//:                                            ://
//:     DATA pointers                          ://
//:                                            ://
//: can be safely casted back and              ://
//: forth between (void*) without change.      ://
//: This contract is NOT the case for          ://
//:                                            ://
//:     FUNCTION pointers.                     ://
//:                                            ://
typedef                                     //:://
    void                                    //:://
    (*MAKEWIND_FUNC)(                      //:://
        void                                //:://
    );                                      //:://
//:____________________________________________://


//:Pointer to: "makewind_GPA"
typedef
    MAKEWIND_FUNC
    (*makewind_pfn_GPA)(
    /**/c_LPCSTR_b08_1B  function_name
    ,         v_HMODULE  dll_containing_function
    ); 



//:TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT://

//////////////////////////////////////////////////
//| Create a mini library for the function     |//
//| pointers you need to create your window.   |//
//////////////////////////////////////////////////

typedef
    void
    (*A_D_A_N_Z_makewind_function_pointer)(
    /**/void*  ptr_01
    ,   void*  ptr_02
    ); 

void
makewind_AssertDifferentAndNonZero(
/**/void* ptr_01
,   void* ptr_02
){
    int has_error = 0;

    if(NULL==ptr_01){
        has_error++;
        printf("[ptr_01:NULL]");
    };;
    if(NULL==ptr_02){
        has_error++;
        printf("[ptr_02:NULL]");
    };;
    if( 0 != has_error ){
        printf(
            "[FAIL:AssertDifferentAndNonZero]\n"
        );;
        fflush( stdout );
        exit( 666 );
    };;

    if( ptr_01 == ptr_02 ){
        has_error++;
        printf("[FAIL:ptr_01==ptr_02]");
        fflush( stdout );
        exit( 666 );
    };;

} //[makewind_AssertDifferentAndNonZero]//

v_HINSTANCE
makewind_LoadLibrary( 
    const char* dll_name //:Example: "user32.dll"
){
    v_HINSTANCE dll_handle =(
        LoadLibraryA( dll_name )
    );;
    if(NULL==dll_handle){
        printf("[makewind:Failed_To_Load_DLL]");
        printf("[dll_name]:%s", dll_name );
        fflush(stdout);
        exit(666);
    };;
    
    return( dll_handle );
} //[makewind_LoadLibrary]//

//:GPA=="GetProcAddress"
MAKEWIND_FUNC
makewind_GPA(
/**/c_LPCSTR_b08_1B                 function_name
,   v_HMODULE   dll_containing_function
){
    if(NULL==dll_containing_function){
        printf("[null:dll_containing_function]");
        fflush( stdout );
        exit( 666 );
    };;

    f_FARPROC function_pointer =(
        GetProcAddress(
        /**/dll_containing_function
        ,   function_name
        )
    );;

    if(NULL==function_pointer){
        printf("[makewind:null:fn_ptr]");
        fflush( stdout );
        exit( 666 );
    };;

    return( (MAKEWIND_FUNC)function_pointer );
} //[makewind_GPA]//

















//[¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯]//
//[BEG: function_pointer_typedefs_for_dll_funcs]//
//|DT=="DLL_TYPEDEFS"                  |////[DT]//
//|[A][B]                              |////[DT]//
//:[C]-----------------------------------------://


typedef
    int 
    (*makewind_pfn_ChoosePixelFormat)(
        HDC                           hdc
    ,   const PIXELFORMATDESCRIPTOR *ppfd
    );

typedef                                   //[DT]//
    BOOL_i32_4B                           //[DT]//
    (*makewind_pfn_CloseHandle)(         //[DT]//
        v_HANDLE hObject                  //[DT]//
    );                                    //[DT]//
typedef                                   //[DT]//
    v_HANDLE                              //[DT]//
    (*makewind_pfn_CreateThread)(        //[DT]//
                                          //[DT]//
    /**/s_LPSECURITY_ATTRIBUTES           //[DT]//
        lpThreadAttributes                //[DT]//
                                          //[DT]//
    ,   SIZE_T_u64_8B                     //[DT]//
        dwStackSize                       //[DT]//
                                          //[DT]//
    ,   LPTHREAD_START_ROUTINE            //[DT]//
        lpStartAddress                    //[DT]//
                                          //[DT]//
    ,   v_HINSTANCE                       //[DT]//
        lpParameter                       //[DT]//
                                          //[DT]//
    ,   DWORD_u32_4B                      //[DT]//
        dwCreationFlags                   //[DT]//
                                          //[DT]//
    ,   LPDWORD                           //[DT]//
        lpThreadId                        //[DT]//
                                          //[DT]//
    );                                    //[DT]//
typedef                                   //[DT]//
    v_HWND                                //[DT]//
    (*makewind_pfn_CreateWindowExW)(     //[DT]//
                                          //[DT]//
    /**/ DWORD_u32_4B dwExStyle   //|01|////[DT]//
    ,c_LPCWSTR_b16_2B lpClassName //|02|////[DT]//
    ,c_LPCWSTR_b16_2B lpWindowName//|03|////[DT]//
    ,    DWORD_u32_4B dwStyle     //|04|////[DT]//
    ,             int X           //|05|////[DT]//
    ,             int Y           //|06|////[DT]//
    ,             int nWidth      //|07|////[DT]//
    ,             int nHeight     //|08|////[DT]//
    ,          v_HWND hWndParent  //|09|////[DT]//
    ,         v_HMENU hMenu       //|10|////[DT]//
    ,     v_HINSTANCE hInstance   //|11|////[DT]//
    ,     v_HINSTANCE lpParam     //|12|////[DT]//
    );                                    //[DT]//
//:[D]-----------------------------------------://
typedef                                   //[DT]//
    LRESULT_i64_8B                        //[DT]//
    (*makewind_pfn_DefWindowProcW)(      //[DT]//
    /**/          v_HWND  hWnd            //[DT]//
    ,        UINT_u32_4B  Msg             //[DT]//
    ,      WPARAM_u64_8B  wParam          //[DT]//
    ,      LPARAM_i64_8B  lParam          //[DT]//
    );                                    //[DT]//
typedef                                   //[DT]//
    LRESULT_i64_8B                        //[DT]//
    (*makewind_pfn_DispatchMessageW)(    //[DT]//
        const MSG_48B *lpMsg              //[DT]//
    );                                    //[DT]//
typedef                                   //[DT]//
    BOOL_i32_4B                           //[DT]//
    (*makewind_pfn_DestroyWindow)(       //[DT]//
        v_HWND hWnd                       //[DT]//
    );                                    //[DT]//
//:[E][F]                                 //[DT]//
//:[G]-----------------------------------------://
typedef
    BOOL_i32_4B
    (*makewind_pfn_GetClientRect)(
    /**/v_HWND      hWnd
    ,   s_RECT    lpRect
    );

typedef                                   //[DT]//
    v_HWND                                //[DT]//
    (*makewind_pfn_GetDesktopWindow)(    //[DT]//
        void                              //[DT]//
    );                                    //[DT]//
typedef                                   //[DT]//
    f_FARPROC                             //[DT]//
    (*makewind_pfn_GetProcAddress)(      //[DT]//
    /**/       v_HMODULE  hModule         //[DT]//
    ,    c_LPCSTR_b08_1B  lpProcName      //[DT]//
    );                                    //[DT]//
typedef                                   //[DT]//
    v_HANDLE                              //[DT]//
    (*makewind_pfn_GetProcessHeap)(      //[DT]//
        void                              //[DT]//
    );                                    //[DT]//
typedef                                   //[DT]//
    v_HGDIOBJ                             //[DT]//
    (*makewind_pfn_GetStockObject)(      //[DT]//
        int                               //[DT]//
    );                                    //[DT]//


typedef
    HDC 
    (*makewind_pfn_GetWindowDC)(
        HWND hWnd
    );

typedef
    HMODULE 
    (*makewind_pfn_GetModuleHandleW)(
        LPCWSTR lpModuleName
    );





//:[H]-----------------------------------------://
typedef                                   //[DT]//
    v_HINSTANCE                           //[DT]//
    (*makewind_pfn_HeapAlloc)(           //[DT]//
    /**/        v_HANDLE  hHeap           //[DT]//
    ,       DWORD_u32_4B  dwFlags         //[DT]//
    ,      SIZE_T_u64_8B  dwBytes         //[DT]//
    );                                    //[DT]//
typedef                                   //[DT]//
    BOOL_i32_4B                           //[DT]//
    (*makewind_pfn_HeapFree)(            //[DT]//
    /**/        v_HANDLE  hHeap           //[DT]//
    ,       DWORD_u32_4B  dwFlags         //[DT]//
    ,        v_HINSTANCE  lpMem           //[DT]//
    );                                    //[DT]//
//:[I][J][K]                              //[DT]//
//:[L]-----------------------------------------://
typedef                                   //[DT]//
    v_HCURSOR                             //[DT]//
    (*makewind_pfn_LoadCursorA)(         //[DT]//
    /**/     v_HINSTANCE  hInstance       //[DT]//
    ,    c_LPCSTR_b08_1B  lpCursorName    //[DT]//
    );                                    //[DT]//
typedef                                   //[DT]//
    v_HICON                               //[DT]//
    (*makewind_pfn_LoadIconA)(           //[DT]//
    /**/     v_HINSTANCE  hInstance       //[DT]//
    ,    c_LPCSTR_b08_1B  lpIconName      //[DT]//
    );                                    //[DT]//
//:[M]-----------------------------------------://
typedef                                   //[DT]//
    int                                   //[DT]//
    (*makewind_pfn_MessageBoxW)(         //[DT]//
    /**/          v_HWND  hWnd            //[DT]//
    ,   c_LPCWSTR_b16_2B  lpText          //[DT]//
    ,   c_LPCWSTR_b16_2B  lpCaption       //[DT]//
    ,        UINT_u32_4B  uType           //[DT]//
    );                                    //[DT]//
//:[N][O]                                 //[DT]//
//:[P]-----------------------------------------://
typedef                                   //[DT]//
    BOOL_i32_4B                           //[DT]//
    (*makewind_pfn_PeekMessageW)(        //[DT]//
    /**/      LPMSG  lpMsg                //[DT]//
    ,        v_HWND  hWnd                 //[DT]//
    ,   UINT_u32_4B  wMsgFilterMin        //[DT]//
    ,   UINT_u32_4B  wMsgFilterMax        //[DT]//
    ,   UINT_u32_4B  wRemoveMsg           //[DT]//
    );                                    //[DT]//
typedef                                   //[DT]//
    void                                  //[DT]//
    (*makewind_pfn_PostQuitMessage)(     //[DT]//
                int  nExitCode            //[DT]//
    );                                    //[DT]//
//:[Q]                                    //[DT]//
//:[R]-----------------------------------------://
typedef                                   //[DT]//
    ATOM_u16_2B                           //[DT]//
    (*makewind_pfn_RegisterClassExW)(    //[DT]//
        const makewind_WNDCLASSEXW *Arg1 //[DT]//
    );                                    //[DT]//
//:[S]-----------------------------------------://
typedef                                   //[DT]//
    v_HWND                                //[DT]//
    (*makewind_pfn_SetFocus)(            //[DT]//
             v_HWND  hWnd                 //[DT]//
    );                                    //[DT]//
typedef
    BOOL 
    (*makewind_pfn_SetPixelFormat)(
        HDC                            hdc
    ,   int                         format
    ,   const PIXELFORMATDESCRIPTOR  *ppfd
    );
typedef                                   //[DT]//
    BOOL_i32_4B                           //[DT]//
    (*makewind_pfn_ShowWindow)(          //[DT]//
    /**/     v_HWND  hWnd                 //[DT]//
    ,           int  nCmdShow             //[DT]//
    );                                    //[DT]//
typedef
    BOOL_i32_4B
    (*makewind_pfn_SwapBuffers)(
        HDC Arg1
    );
   
//:[T]-----------------------------------------://
typedef                                   //[DT]//
    BOOL_i32_4B                           //[DT]//
    (*makewind_pfn_TranslateMessage)(    //[DT]//
        const MSG_48B *lpMsg              //[DT]//
    );                                    //[DT]//
//:[U]-----------------------------------------://
typedef                                   //[DT]//
    BOOL_i32_4B                           //[DT]//
    (*makewind_pfn_UpdateWindow)(        //[DT]//
        v_HWND hWnd                       //[DT]//
    );                                    //[DT]//
//:[V]                                    //[DT]//
//:[W]-----------------------------------------://
typedef                                   //[DT]//
    DWORD_u32_4B                          //[DT]//
    (*makewind_pfn_WaitForSingleObject)( //[DT]//
    /**/    v_HANDLE  hHandle             //[DT]//
    ,   DWORD_u32_4B  dwMilliseconds      //[DT]//
    );                                    //[DT]//
//:[X][Y][Z]                              //[DT]//
//[END: function_pointer_typedefs_for_dll_funcs]//
//[____________________________________________]//

struct gleb_SWIN_FUNCTION_POINTERS {
  
    struct MAKEWIND_LOADED_DLLS {

        v_HINSTANCE gdi32   ; //[07(g|G)]//
        v_HINSTANCE kernel32; //[11(k|K)]//
        v_HINSTANCE user32  ; //[21(u|U)]//
        
    }DLL;

    //:functions from gdi32.dll
    struct makewind_functions_GDI32{

        struct  makewind_data_GDI32{
            struct makewind_brushes_GDI32{

                int BLACK; //:BLACK_BRUSH

            }BRUSH ;
        }DATA ;

        makewind_pfn_ChoosePixelFormat
                      ChoosePixelFormat;

        makewind_pfn_GetStockObject
                      GetStockObject;

        makewind_pfn_SetPixelFormat
                      SetPixelFormat;

        makewind_pfn_SwapBuffers
                      SwapBuffers;

    }GDI32;

    //:Functions from kernel32.dll
    struct makewind_functions_KERNEL32{

        struct  makewind_data_KERNEL32{

            
            DWORD_u32_4B heap_zero_memory;
            DWORD_u32_4B wait_failed;
            DWORD_u32_4B infinite;
            

        }DATA;

        //:[A][B]
        //:[C]---------------------------------://
        makewind_pfn_CreateThread
                      CreateThread   ;

        makewind_pfn_CloseHandle
                      CloseHandle   ;

        //:[D][E][F]---------------------------://
        //:[G]---------------------------------://

        makewind_pfn_GetModuleHandleW
                      GetModuleHandleW;

        makewind_pfn_GetProcessHeap
                      GetProcessHeap ;
       
        //:[H]---------------------------------://
        makewind_pfn_HeapAlloc 
                      HeapAlloc ;

        makewind_pfn_HeapFree  
                      HeapFree ;

        //:[I][J][K][L][M][N][O][P][Q][R][S][T]://
        //:[U][V]------------------------------://
        //:[W]---------------------------------://
        makewind_pfn_WaitForSingleObject
                      WaitForSingleObject   ;
    
    }KERNEL32;

    //:Functions from user32.dll
    struct makewind_functions_USER32{

        struct  makewind_data_USER32{

            int sw_show;

            UINT_u32_4B       wm_quit;
            uintptr_t     pm_noremove;
            uintptr_t       pm_remove;

            //|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|//
            //| MessageBox Values     |//
            //|- - - - - - - - - - - -|//
            //|                       |//
            //|0x00000030L         //||//
                UINT_u32_4B        //||//
                mb_iconexclamation;//||//
            //|                       |//
            //|0x00000000L         //||//
                UINT_u32_4B        //||//
                mb_ok          ;   //||//
            //|_______________________|//

            UINT_u32_4B cs_owndc;

            UINT_u32_4B ws_ex_topmost;

            //: #define U32 GLEB_DWORD_UINT32;
            //:--------------------------+  
            UINT_u32_4B ws_overlappedwindow; // |  
            UINT_u32_4B      ws_tiledwindow; // |  
            //:-------------------:// // |  
            UINT_u32_4B      ws_caption    ; // |  
            UINT_u32_4B      ws_maximizebox; // |  
            UINT_u32_4B      ws_minimizebox; // |  
            UINT_u32_4B      ws_overlapped ; // |  
            UINT_u32_4B      ws_sysmenu    ; // |  
            UINT_u32_4B      ws_thickframe ; // |  
            //:--------------------------+  
            

            //:"ASC" and "UNI" instead of
            //:"ASCII" and "UNICODE" because
            //: afraid of collision with macros.
            struct 
            makewind_data_ASCII_USER32{

                c_LPCSTR_b08_1B idi_application  ;
                c_LPCSTR_b08_1B idc_arrow        ;

            }A; //:ASCII
            struct 
            makewind_data_UNICODE_USER32{
        
                //[NOT_IMPLEMENTED]//
                int unused;

            }W; //:UNICODE/WIDE
        }DATA;

        //:[A][B]
        //:[C]---------------------------------://
        makewind_pfn_CreateWindowExW
                      CreateWindowExW;
        //:[D]---------------------------------://
        makewind_pfn_DefWindowProcW
                      DefWindowProcW;

        makewind_pfn_DestroyWindow
                      DestroyWindow;

        makewind_pfn_DispatchMessageW
                      DispatchMessageW;
        //:[E][F]
        //:[G]---------------------------------://
        makewind_pfn_GetClientRect
                      GetClientRect;

        makewind_pfn_GetDesktopWindow
                      GetDesktopWindow;

        makewind_pfn_GetWindowDC
                      GetWindowDC;
        //:[H][I][J][K]
        //:[L]---------------------------------://
        makewind_pfn_LoadCursorA
                      LoadCursorA;

        makewind_pfn_LoadIconA
                      LoadIconA;
        //:[M]---------------------------------://
        makewind_pfn_MessageBoxW
                      MessageBoxW;

        //:[N][O]
        //:[P]---------------------------------://
        makewind_pfn_PeekMessageW
                      PeekMessageW;

        makewind_pfn_PostQuitMessage
                      PostQuitMessage;
        //:[Q]
        //:[R]---------------------------------://
        makewind_pfn_RegisterClassExW
                      RegisterClassExW;
        //:[S]---------------------------------://
        makewind_pfn_SetFocus
                      SetFocus;

        makewind_pfn_ShowWindow
                      ShowWindow;
        //:[T]---------------------------------://
        makewind_pfn_TranslateMessage
                      TranslateMessage;
        //:[U]---------------------------------://
        makewind_pfn_UpdateWindow
                      UpdateWindow;
        //:[V][W][X][Y][Z]


        

    }USER32;

}makewind_function_pointers;
typedef 
    struct gleb_SWIN_FUNCTION_POINTERS
    struct_gleb_SWIN_FUNCTION_POINTERS;
void  init_gleb_SWIN_FUNCTION_POINTERS( void ){

    struct_gleb_SWIN_FUNCTION_POINTERS*
    FP=&(makewind_function_pointers);

    //:Load DLLS:
    //////////////////////////////////////////////

    FP->DLL.gdi32=makewind_LoadLibrary(
           "gdi32" );;

    FP->DLL.kernel32=makewind_LoadLibrary(
           "kernel32" );;

    FP->DLL.user32=makewind_LoadLibrary(
           "user32" );;

    //:Make sure you didn't accidentially swap
    //:any function pointer addresses:
    //|-  --  --  --  --  --  --  --  --  --  -|//
    A_D_A_N_Z_makewind_function_pointer
    A_D_A_N_Z=&( 
        makewind_AssertDifferentAndNonZero 
    );;

    A_D_A_N_Z( FP->DLL.gdi32,
               FP->DLL.kernel32  );;

    A_D_A_N_Z( FP->DLL.kernel32,
               FP->DLL.user32    );;

    A_D_A_N_Z( FP->DLL.user32,
               FP->DLL.gdi32     );;
    //|-  --  --  --  --  --  --  --  --  --  -|//

    //////////////////////////////////////////////

    //:Load FUNCTIONS from DLLS:
    //////////////////////////////////////////////

    makewind_pfn_GPA
    G=&(makewind_GPA);

    //:G: GDI32:
    //:GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG://
                                           //[G]//
    //:DATA:                               //[G]//
    FP->GDI32.DATA.BRUSH.BLACK = 4;        //[G]//
                                           //[G]//
    #define T(n) typedef makewind_pfn_ ## n
    T( ChoosePixelFormat ) G_01;           //[G]//
    T( GetStockObject    ) G_02;           //[G]//
    T( SetPixelFormat    ) G_03;           //[G]//
    T( SwapBuffers       ) G_04;           //[G]//
    #undef T                               //[G]//
                                           //[G]//
    FP->/**/GDI32                          //[G]//
        .ChoosePixelFormat=(G_01)(G(       //[G]//
        "ChoosePixelFormat" ,              //[G]//
    FP->DLL.gdi32 ));;                     //[G]//
                                           //[G]//
    FP->/**/GDI32                          //[G]//
        .GetStockObject   =(G_02)(G(       //[G]//
        "GetStockObject" ,                 //[G]//
    FP->DLL.gdi32 ));;                     //[G]//
                                           //[G]//
    FP->/**/GDI32                          //[G]//
        .SetPixelFormat   =(G_03)(G(       //[G]//
        "SetPixelFormat" ,                 //[G]//
    FP->DLL.gdi32 ));;                     //[G]//
                                           //[G]//
    FP->/**/GDI32                          //[G]//
        .SwapBuffers      =(G_04)(G(       //[G]//
        "SwapBuffers" ,                    //[G]//
    FP->DLL.gdi32 ));;                     //[G]//
                                           //[G]//
    //:GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG://
    //:K: KERNEL32:
    //:KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK://


    struct makewind_data_KERNEL32*
    K32D = &(         
        FP->KERNEL32.DATA 
    );;
              
    K32D -> heap_zero_memory = 0x00000008;
    K32D -> wait_failed      = 0xFFFFFFFF;
    K32D -> infinite         = 0xffffffff;

    #define T(n) typedef makewind_pfn_ ## n
    T( CloseHandle         ) K_01;       //[K32]//
    T( CreateThread        ) K_02;       //[K32]//
    T( HeapAlloc           ) K_03;       //[K32]//
    T( HeapFree            ) K_04;       //[K32]//
    T( GetModuleHandleW    ) K_05; 
    T( GetProcessHeap      ) K_06;       //[K32]//
    T( WaitForSingleObject ) K_07;       //[K32]//
    #undef T                             //[K32]//
                                         //[K32]//
    FP->/**/KERNEL32                     //[K32]//
        .CloseHandle        =(K_01)(G(   //[K32]//
        "CloseHandle" ,                  //[K32]//
    FP->DLL.kernel32 ));;                //[K32]//
                                         //[K32]//
    FP->/**/KERNEL32                     //[K32]//
        .CreateThread       =(K_02)(G(   //[K32]//
        "CreateThread" ,                 //[K32]//
    FP->DLL.kernel32 ));;                //[K32]//
                                         //[K32]//
    FP->/**/KERNEL32                     //[K32]//
        .HeapAlloc          =(K_03)(G(   //[K32]//
        "HeapAlloc" ,                    //[K32]//
    FP->DLL.kernel32 ));;                //[K32]//
                                         //[K32]//
    FP->/**/KERNEL32                     //[K32]//
        .HeapFree           =(K_04)(G(   //[K32]//
        "HeapFree" ,                     //[K32]//
    FP->DLL.kernel32 ));;                //[K32]//
                                         //[K32]//
    FP->/**/KERNEL32                     //[K32]//
        .GetModuleHandleW   =(K_05)(G(   //[K32]//
        "GetModuleHandleW" ,             //[K32]//
    FP->DLL.kernel32 ));;                //[K32]//

    FP->/**/KERNEL32                     //[K32]//
        .GetProcessHeap     =(K_06)(G(   //[K32]//
        "GetProcessHeap" ,               //[K32]//
    FP->DLL.kernel32 ));;                //[K32]//
                                         //[K32]//
    FP->/**/KERNEL32                     //[K32]//
        .WaitForSingleObject=(K_07)(G(   //[K32]//
        "WaitForSingleObject" ,          //[K32]//
    FP->DLL.kernel32 ));;                //[K32]//
                                         //[K32]//
    //:U: USER32:                        //[K32]//
    //:UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU://
                                         //[U32]//
    struct makewind_data_USER32*        //[U32]//
    U32D = &(                            //[U32]//
        FP->USER32.DATA                  //[U32]//
    );;                                  //[U32]//
                                         //[U32]//
    U32D -> sw_show     = 5;             //[U32]//
                                         //[U32]//
    U32D -> wm_quit     = 0x0012;        //[U32]//
    U32D -> pm_noremove = 0x0000;        //[U32]//
    U32D -> pm_remove   = 0x0001;        //[U32]//
                                         //[U32]//
                                         //[U32]//
    U32D -> mb_iconexclamation =(        //[U32]//
                    0x00000030L          //[U32]//
    );;                                  //[U32]//
    U32D -> mb_ok =(                     //[U32]//
                    0x00000000L          //[U32]//
    );;                                  //[U32]//
                                         //[U32]//
    U32D -> cs_owndc    = 0x0020;        //[U32]//
                                         //[U32]//
    U32D -> ws_ex_topmost  = 0x00000008L;//[U32]//
                                         //[U32]//
    U32D -> ws_caption     = 0x00C00000L;//[U32]//
    U32D -> ws_maximizebox = 0x00010000L;//[U32]//
    U32D -> ws_minimizebox = 0x00020000L;//[U32]//
    U32D -> ws_overlapped  = 0x00000000L;//[U32]//
    U32D -> ws_sysmenu     = 0x00080000L;//[U32]//
    U32D -> ws_thickframe  = 0x00040000L;//[U32]//
                                         //[U32]//
    UINT_u32_4B                          //[U32]//
    same =(                              //[U32]//
        U32D -> ws_overlapped  |         //[U32]//
        U32D -> ws_caption     |         //[U32]//
        U32D -> ws_sysmenu     |         //[U32]//
        U32D -> ws_thickframe  |         //[U32]//
        U32D -> ws_minimizebox |         //[U32]//
        U32D -> ws_maximizebox |         //[U32]//
    0);;                                 //[U32]//
                                         //[U32]//
    //:Both are the same exact style:    //[U32]//
    U32D -> ws_overlappedwindow = same;  //[U32]//
    U32D -> ws_tiledwindow      = same;  //[U32]//
                                         //[U32]//
    U32D -> A.idi_application=(          //[U32]//
        //: [0111][1111][0000][0000]     //[U32]//
        MAKEINTRESOURCEA( 32512 )        //[U32]//
    );;                                  //[U32]//
    U32D -> A.idc_arrow=(                //[U32]//
        //: [0111][1111][0000][0000]     //[U32]//
        MAKEINTRESOURCEA( 32512 )        //[U32]//
    );;                                  //[U32]//
                                         //[U32]//
    //+----------------------------------------+//
    //|EXAMPLE_MACRO_USAGE:                 U32|//
    //|T( Update ) U_99;                    U32|//
    //|                                     U32|//
    //|AFTER_PRE_PROCESSING:                U32|//
    //|typedef makewind_pfn_Update U_99;   U32|//
    //+----------------------------------------+//
    #define T(n) typedef makewind_pfn_ ## n
    T( CreateWindowExW  )  U_01;         //[U32]//
    T( DefWindowProcW   )  U_02;         //[U32]//
    T( DestroyWindow    )  U_03;         //[U32]//
    T( DispatchMessageW )  U_04;         //[U32]//
    T( GetClientRect    )  U_05;         //[U32]//
    T( GetDesktopWindow )  U_06;         //[U32]//
    T( GetWindowDC      )  U_07;         //[U32]//
    T( LoadCursorA      )  U_08;         //[U32]//
    T( LoadIconA        )  U_09;         //[U32]//
    T( MessageBoxW      )  U_10;         //[U32]//
    T( PeekMessageW     )  U_11;         //[U32]//
    T( PostQuitMessage  )  U_12;         //[U32]//
    T( RegisterClassExW )  U_13;         //[U32]//
    T( SetFocus         )  U_14;         //[U32]//
    T( ShowWindow       )  U_15;         //[U32]//
    T( TranslateMessage )  U_16;         //[U32]//
    T( UpdateWindow     )  U_17;         //[U32]//
    #undef T                             //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .CreateWindowExW   =(U_01)(G(    //[U32]//
        "CreateWindowExW" ,              //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .DefWindowProcW    =(U_02)(G(    //[U32]//
        "DefWindowProcW" ,               //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .DestroyWindow     =(U_03)(G(    //[U32]//
        "DestroyWindow" ,                //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .DispatchMessageW  =(U_04)(G(    //[U32]//
        "DispatchMessageW",              //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .GetClientRect     =(U_05)(G(    //[U32]//
        "GetClientRect",                 //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .GetDesktopWindow  =(U_06)(G(    //[U32]//
        "GetDesktopWindow",              //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .GetWindowDC       =(U_07)(G(    //[U32]//
        "GetWindowDC",                   //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .LoadCursorA       =(U_08)(G(    //[U32]//
        "LoadCursorA" ,                  //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .LoadIconA         =(U_09)(G(    //[U32]//
        "LoadIconA" ,                    //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .MessageBoxW       =(U_10)(G(    //[U32]//
        "MessageBoxW" ,                  //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .PeekMessageW      =(U_11)(G(    //[U32]//
        "PeekMessageW" ,                 //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .PostQuitMessage   =(U_12)(G(    //[U32]//
        "PostQuitMessage" ,              //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .RegisterClassExW  =(U_13)(G(    //[U32]//
        "RegisterClassExW" ,             //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .SetFocus          =(U_14)(G(    //[U32]//
        "SetFocus" ,                     //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .ShowWindow        =(U_15)(G(    //[U32]//
        "ShowWindow" ,                   //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .TranslateMessage  =(U_16)(G(    //[U32]//
        "TranslateMessage",              //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //                                   //[U32]//
    FP->/**/USER32                       //[U32]//
        .UpdateWindow      =(U_17)(G(    //[U32]//
        "UpdateWindow" ,                 //[U32]//
    FP->DLL.user32 ));;                  //[U32]//
    //:UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU://
                                           //[P]//
    //[ [NICE_TO_HAVE]:                      [P]//
    //[ Every block should add function      [P]//
    //[ pointer to a temporary array then    [P]//
    //[ do simple n * n loop to make sure    [P]//
    //[ all addresses are unique. Also       [P]//
    //[ check for non-null while at it.      [P]//
                                           //[P]//
} //[init_gleb_SWIN_FUNCTION_POINTERS]//   //[P]//
//[PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP]//



//[GSGSGSGSGSGSGSGSGSGSGSGSGSGSGSGSGSGSGSGSGSGS]//
//! Sample custom data structure for threads GS!//
//! to use. This is passed by void pointer   GS!//
//! so it can be any data type that can be   GS!//
//! passed using a single void pointer       GS!//
//! (LPVOID).                                GS!//
typedef struct makewind_MyData {         //|GS|//
    int val1;                             //|GS|//
    int val2;                             //|GS|//
}  makewind_MYDATA                       //|GS|//
, *makewind_PMYDATA                      //|GS|//
; //[makewind_MyData]//                  //|GS|//
                                          //|GS|//
//!GS.PW.W32.<SomeWindowVariable>            GS!//
struct 
makewind_global_state{                   //|GS|//
                                          //|GS|//
             int         init_called ;    //|GS|//   
             int       init_finished ;    //|GS|//   
    volatile int      window_created ;    //|GS|//
     
    
    struct //:#notification_flags#
    makewind_thread_safe_notify_flags_x64{
    
        #define T64 LONG64 volatile //:64bit int.
        T64  resize_message_count;
        T64  redraw_message_count;
        #undef  T64

    }THREAD_SAFE_FLAGS;

    //+ Use a mutex instead to signal to other    +//
    //+ threads when certain events have happened.+//
    //- struct                                    -//
    //- makewind_optional_callback_funcs{        -//
    //-                                           -//
    //-     void(  *render_tick_function)(void);  -//
    //-     int     render_tick_function_has;     -//
    //-                                           -//
    //-     void(  *resize_function)(void);       -//
    //-     int     resize_function_has;          -//
    //-                                           -//
    //-                                           -//
    //- }OPTIONAL_CALLBACKS;                      -//
                                          
                                          //|GS|//
    //|"just_closed" because the window      GS|//
    //|thread has not been terminated and    GS|//
    //|no resources have been cleaned        GS|//
    //|up yet.                               GS|//
    volatile int  window_just_closed ;    //|GS|//
                                          //|GS|//
    //!Window Position And Size:             GS!//
    int X  ;                              //|GS|//
    int Y  ;                              //|GS|//
    int WID;                              //|GS|//
    int HIG;                              //|GS|//
                                          //|GS|//
    //!PW:PLATFORM_WINDOW                    GS!//
    struct makewind_PLATFORM_WINDOW{     //|GS|//
                                          //|GS|//
    //!Eventually, windows and linux         GS!//
    //!structs should be wrapped in          GS!//
    //!#ifdef blocks:                        GS!//
    //!(This will probably never happen)     GS!//
    //!(I think I'll keep it simple and)     GS!//
    //!(stick to windows only.         )     GS!//
    //!_                                     GS!//
    //! |                                    GS!//
        struct makewind_PW_WINDOWS{      //|GS|//
                                          //|GS|//
            PIXELFORMATDESCRIPTOR         //|GS|//
            pixel_format_descriptor;      //|GS|//
                                          //|GS|//
           HWND handle_to_window     ;    //|GS|//
            HDC window_device_context;    //|GS|//
                                          //|GS|//
    //!This thread only handles window       GS!//
    //!display and window input. We do       GS!//
    //!this so we can keep tutorial code     GS!//
    //!written in a linear way even after    GS!//
    //!the window is created.                GS!//
    //!                                      GS!//
    //!If window was on same thread as       GS!//
    //!tutorial, we would have to juggle     GS!//
    //!calling the window update loop        GS!//
    //!code while at the same time           GS!//
    //!calling tutorial functions.           GS!//
    //!____                                  GS!//
    //!    |                                 GS!//
            v_HANDLE                      //|GS|//
            platform_window_thread;       //|GS|//
                                          //|GS|//
    //!Thread is closed using the HANDLE.    GS!//
    //!So not sure what the point of         GS!//
    //!the thread_id is.                     GS!//
    //!                                      GS!//
    //!StackOverflow:                        GS!//
    //!Under Windows, the thread handle      GS!//
    //!is different from the thread ID,      GS!//
    //!in the same way that a file handle    GS!//
    //!is different from a file name.        GS!//
    //!____                                  GS!//
    //!    |                                 GS!//
            long unsigned int             //|GS|//
            thread_id;                    //|GS|//
                                          //|GS|//
    //!custom data object that can be        GS!//
    //!passed to the thread creation         GS!//
    //!function.                             GS!//
    //!____                                  GS!//
    //!    |                                 GS!//
            makewind_PMYDATA             //|GS|//
            custom_data;                  //|GS|//
                                          //|GS|//
        }W32;                             //|GS|//
        struct makewind_PW_LINUX{        //|GS|//
                                          //|GS|//
            //!It's a nice thought,          GS!//
            //!But I'll probably never       GS!//
            //!make this code flexible       GS!//
            //!enough to also compile        GS!//
            //!on linux.                     GS!//
            int unused;                   //|GS|//
                                          //|GS|//
        }LIN;                             //|GS|//
                                          //|GS|//
    }PW;                                  //|GS|//
                                          //|GS|//
    //| StructAdded[DATE[2019_06_18]]       |GS|//
    //| MAKEWIND.GetClient.X(   void );    |GS|//
    //| MAKEWIND.GetClient.Y(   void );    |GS|//
    //| MAKEWIND.GetClient.WID( void );    |GS|//
    //| MAKEWIND.GetClient.HIG( void );    |GS|//
    struct MAKEWIND_GetClient{

        int (*  X)( void );
        int (*  Y)( void );
        int (*WID)( void );
        int (*HIG)( void );

    }GetClient;


}MAKEWIND={0}; 
             
typedef                                   //|GS|//
    struct makewind_global_state         //|GS|//
    struct_makewind_global_state;        //|GS|//
                                          //|GS|//
//! Its not just enough to create a window,  GS!//
//! the window must have the proper pixel    GS!//
//! format descriptor associated with it's   GS!//
//! device context for open gl to work.      GS!//
//!                                          GS!//
//!  YOU ONLY GET ONE SHOT!                  GS!//
//!  YOU CAN ONLY SET IT ONCE!               GS!//
//!                                          GS!//
//!  https://www.khronos.org/opengl/wiki     GS!//
//!  /Creating_an_OpenGL_Context_(WGL)       GS!//
void                                      //|GS|//
makewind_InitPixelFormatDescriptor(      //|GS|//
    void                                  //|GS|//
){                                        //|GS|//
                                          //|GS|//
                                          //|GS|//
    PIXELFORMATDESCRIPTOR                 //|GS|//
    pixel_format_descriptor ={            //|GS|//
        sizeof(PIXELFORMATDESCRIPTOR),    //|GS|//
        1,                                //|GS|//
                                          //|GS|//
        (   //! Flags________!//          //|GS|//
            PFD_DRAW_TO_WINDOW |          //|GS|//
            PFD_SUPPORT_OPENGL |          //|GS|//
            PFD_DOUBLEBUFFER   |          //|GS|//
        0)                                //|GS|//
                                          //|GS|//
        ,                                 //|GS|//
                                          //|GS|//
        //! The kind of framebuffer.         GS!//
        //! RGBA or palette.                 GS!//
        PFD_TYPE_RGBA,                    //|GS|//
                                          //|GS|//
        //! Colordepth of the framebuffer.   GS!//
        32,                               //|GS|//
                                          //|GS|//
        0, 0, 0, 0, 0, 0,                 //|GS|//
        0,                                //|GS|//
        0,                                //|GS|//
        0,                                //|GS|//
        0, 0, 0, 0,                       //|GS|//
                                          //|GS|//
        //! Number_Of_Bits: depthbuffer      GS!//
        24,                               //|GS|//
                                          //|GS|//
        //! Number_Of_Bits: stencilbuffer    GS!//
        8,                                //|GS|//
                                          //|GS|//
        //! Number of Aux buffers            GS!//
        //! in the framebuffer.              GS!//
        0,                                //|GS|//
                                          //|GS|//
        PFD_MAIN_PLANE,                   //|GS|//
        0,                                //|GS|//
        0, 0, 0                           //|GS|//
    };;                                   //|GS|//
                                          //|GS|//
    //! Copy memory. For a brief moment We   GS!//
    //! are using double memory for the      GS!//
    //! pixel format descriptor,but easiest  GS!//
    //! way I can think of to get it         GS!//
    //! properly initialized and put into    GS!//
    //! global state container as            GS!//
    //! NON-Pointer.                         GS!//
    MAKEWIND.PW.W32                      //|GS|//
    .pixel_format_descriptor=(            //|GS|//
        pixel_format_descriptor           //|GS|//
    );;                                   //|GS|//
                                          //|GS|//
} //[InitPixelFormatDescriptor]//         //|GS|//
                                          //|GS|//
void                                      //|GS|//
makewind_InitGlobalStateContainer(       //|GS|//
    void                                  //|GS|//
){                                        //|GS|//
    //+---------------------------+-++-+////|GS|//
    //+---------------------------+-++-+////|GS|//   
    //+ Convinience Methods to help    +////|GS|//
    //+ with formatting of code that   +////|GS|//
    //+ [[USES]] MAKEWIND             +////|GS|//
    //+---------------------------+-++-+////|GS|//
    //+---------------------------+-++-+////|GS|//
    MAKEWIND.GetClient.X   =&( //+ || +////|GS|//
    MAKEWIND_GetClient_X);     //+ || +////|GS|//
                                //+ || +////|GS|//
    MAKEWIND.GetClient.Y   =&( //+ || +////|GS|//
    MAKEWIND_GetClient_Y);     //+ || +////|GS|//
                                //+ || +////|GS|//
    MAKEWIND.GetClient.WID =&( //+ || +////|GS|//
    MAKEWIND_GetClient_WID);   //+ || +////|GS|//
                                //+ || +////|GS|//
    MAKEWIND.GetClient.HIG =&( //+ || +////|GS|//
    MAKEWIND_GetClient_HIG);   //+ || +////|GS|//
    //+---------------------------+-++-+////|GS|//
    //+---------------------------+-++-+////|GS|//
                                          //|GS|//
    makewind_InitPixelFormatDescriptor();//|GS|//
                                          //|GS|//
} //[makewind_InitGlobalStateContainer]////|GS|//
                                          //|GS|//
//[GSGSGSGSGSGSGSGSGSGSGSGSGSGSGSGSGSGSGSGSGSGS]//

//:NULFUN:NullFunctionPointerError
void
makewind_NULFUN( 
    const char* name_of_null_function
){
    printf(
        "[GLEB.SWIN:Null_Func_Pointer_Found]\n"
    );;
    printf( "Null:%s\n", name_of_null_function );
    fflush(stdout);
    exit( 666 );
} //[makewind_NULFUN]//
void
makewind_Halt( 
    const char* error_message_string
){
    printf(
        "[GLEB.SWIN:Fatal_Error_Encountered]\n"
    );;
    printf( "[EMS]:%s\n", error_message_string );
    fflush(stdout);
    exit( 666 );
} //[makewind_Halt]//


int 
makewind_Alert( 
    const char* msg 
){

    printf(
        "[WhatWentWrong]:%s\n", msg
    );;fflush(stdout);

    struct_gleb_SWIN_FUNCTION_POINTERS*
    FP=&(makewind_function_pointers);

    if(NULL==FP->USER32.MessageBoxW){
        const char* msg = "[ForgotToInitMsgBoxW]";
        makewind_Halt( msg  );
    };;

    struct makewind_data_USER32*         
    U32D = &(                             
        FP->USER32.DATA                   
    );;

    int msgboxID =(
    FP->USER32.MessageBoxW(
        NULL
    ,
        L"You forgot to do something in code.\n"
        L"strcat is a lot of work to make a  \n"
        L"custom message. So check the       \n"
        L"console for what went wrong.       \n"
    ,
        L"[!!CHECK_THE_CONSOLE!!]"
    ,
        (
            U32D -> mb_iconexclamation | 
            U32D -> mb_ok              |
        0)
    ));;

    return msgboxID;    
} //[makewind_Alert]//


//| Section:WINDOW_CODE:start -----------------|//
//|WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|//

//:WINDOW_MESSAGE_HANDLER_WNDPROC
//:WIN:WINDOW
//:MSG:MESSAGE
//:HAN:HANDLER
//:WND:WIND
//:POC:PROC
//:WND_POC:WNDPROC
__stdcall
LRESULT_i64_8B   
makewind_WIN_MSG_HAN_WND_POC(
/**/       v_HWND   Hw  
,     UINT_u32_4B   Msg
,   WPARAM_u64_8B   wParam  
,   LPARAM_i64_8B   lParam
){
    //:An LRESULT tells us what we did
    //:with the message. If handled it
    //:should return zero.
    LRESULT_i64_8B return_this_result = 0;
    BOOL_i32_4B ok = 0;

    struct_gleb_SWIN_FUNCTION_POINTERS*
    FP = &(makewind_function_pointers);
    if(NULL==FP->USER32.DestroyWindow){
        makewind_Halt("[U32.DW]");
    };;
    if(NULL==FP->USER32.PostQuitMessage){
        makewind_Halt("[U32.PQM]");
    };;
    if(NULL==FP->USER32.DefWindowProcW){
        makewind_Halt("[U32.DWPW]");
    };;

    switch(Msg){ //:- - - - - - - - - - - - - -://
    case WM_SIZE:{

        printf("[MAKEWIND:WM_SIZE]\n");
        fflush(stdout);

        ENGETHER.THREADING.InterlockedIncrement64(
            &( MAKEWIND.THREAD_SAFE_FLAGS.
               resize_message_count )
        );;

        //: #define C_B MAKEWIND.OPTIONAL_CALLBACKS
        //: if(C_B.resize_function_has){
        //:    C_B.resize_function();
        //: };;
        //: #undef  C_B

        //# [TODO]: #// InterlockedExchangeAddAcquire64( THREAD_SAFE_FLAGS.resize_message_count, 1 );

    }break;
    case WM_KEYDOWN:{
        if(wParam==VK_ESCAPE){

            ok = FP->USER32.DestroyWindow(Hw);
            if(0==ok){makewind_Halt("[0OK_1]");}

        }else{
            //: KEBO_DOWN_HandleVirtualKey( wParam );
        };;

    }break;

    case WM_KEYUP:{
        
            //: KEBO_UPPP_HandleVirtualKey( wParam );

    }break;

    //:WM_CLOSE: The "[X]" button was clicked.
    case WM_CLOSE:
        ok = FP->USER32.DestroyWindow(Hw); 
        if(0==ok){makewind_Halt("[0OK_2]");}

    //:WM_DESTROY: ( DESTROYED|DESTROYING )
    case WM_DESTROY:  
        //: Send "WM_QUIT" to exit msg loop.
        FP->USER32.PostQuitMessage(0);

    case WM_PAINT:
        //:[TODO]:Something to pace the updating
        //:of graphics.


        //+ DELETE THIS BLOCK +//
        //- //:I dont think this is needed:         -//
        //- //: You may use the same HDC in both    -//
        //- //: threads, but not at the same time.  -//
        //- //: SEE[ gl-hdc-thread-quote ]          -//
        //- if(MAKEWIND.render_tick_function_has){ -//
        //-    MAKEWIND.render_tick_function();    -//
        //- };;                                     -//

        //: This might be better done setting a flag
        //: than using a callback. In order to prevent
        //: drawing code from being invoked on the
        //: wrong thread.

        //: With that said, setting a flag:
        ENGETHER.THREADING.InterlockedIncrement64(
            &( MAKEWIND.THREAD_SAFE_FLAGS.
               redraw_message_count )
        );;

        
        //+ This call needs to be made from    +//
        //+ the same thread as your OpenGL     +//
        //+ calls.                             +//
        //# DONT_HERE:MAKEWIND_SwapBuffers(); #//





    //:Keep window responsive:
    default: 
        return_this_result=(
            FP->USER32.DefWindowProcW(
                Hw,Msg,wParam,lParam
            )
        );;
    };;//:- - - - - - - - - - - - - - - - - - -://

    return( return_this_result );
} //[makewind_WIN_MSG_HAN_WND_POC]//




BOOL_i32_4B 
makewind_RegisterWindow(
//+-------------------------+[ ]+//
/**/v_HINSTANCE           //+[1]+//
    hin                   //+[1]+//
                          //+[ ]+//
//+ (UNICODE_STRING)         [ ]+//
,   c_LPCWSTR_b16_2B      //+[2]+//
    unique_window_name    //+[2]+//
//+-------------------------+[ ]+//
){

    struct_gleb_SWIN_FUNCTION_POINTERS*
    FP = &(makewind_function_pointers);

    if(NULL==FP->GDI32.GetStockObject){
        makewind_Halt("[G32.GSO]");
    };;




    //:Before using re-creation of
    //:WNDCLASSEXW, make sure correct size
    //:as a basic smoke test.
    size_t struct_size =(
        sizeof( makewind_WNDCLASSEXW )
    );;
    if( struct_size != 80 ){
        makewind_Halt("[BadStructSize]");
    };;
    


    
    //: WNDCLASSEXW W;
    makewind_WNDCLASSEXW W = {0};

    W.cbSize=sizeof( makewind_WNDCLASSEXW);
    W.style=(
        CS_HREDRAW | //| Copied from glfw's:   |//
        CS_VREDRAW | //| win32_window.c        |//
        CS_OWNDC   | //| _gflwRegisterWindow   |//
                     //| ...ClassWin32         |//
    0);;
    W.lpfnWndProc=makewind_WIN_MSG_HAN_WND_POC;
    W.cbClsExtra=0;
    W.cbWndExtra=0;
    W.hInstance=hin;

    W.hIcon  =FP->USER32.LoadIconA(
        NULL
    ,   FP->USER32.DATA.A.idi_application
    );;
    W.hCursor=FP->USER32.LoadCursorA(
        NULL
    ,   FP->USER32.DATA.A.idc_arrow
    );;

    //| Looking at:                            |//
    //| https://github.com/glfw/glfw/blob/     |//
    //| master/src/win32_window.c              |//
    //| does not look like background          |//
    //| brush color eneds to be set.           |//
    //|                                        |//
    //| Code here specifically says:           |//
    //| "No Background Required For GL"        |//
    //| http://nehe.gamedev.net/tutorial       |//
    //| /creating_an_opengl_window_(win32)     |//
    //| /13001/                                |//
    //- W.hbrBackground=(                      -//
    //-     /**/(HBRUSH)                       -// 
    //-     /**/ FP->GDI32.GetStockObject(     -// 
    //-     /**/     FP->GDI32.DATA.BRUSH.BLACK-// 
    //-     /**/)                              -// 
    //- );;                                    -//
    W.hbrBackground=NULL;

    W.lpszMenuName=NULL;
    W.lpszClassName=unique_window_name;
    W.hIconSm=(
        FP->USER32.LoadIconA(
            NULL
        ,   FP->USER32.DATA.A.idi_application
        )
    );;

    //|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|//
    //! If you forget to register your         !//
    //! window class, the observable effect    !//
    //! is the window never opening, and the   !//
    //! wait loop exiting immediately.         !//
    //|________________________________________|//
    return(
        FP->USER32.RegisterClassExW(
            &( W )
        )
    );;
} //[Register]//

void
makewind_AssertPeekFunctionExists(){

    struct_gleb_SWIN_FUNCTION_POINTERS*
    FP = &(makewind_function_pointers);

    if(NULL==FP){ 
        makewind_Halt("[FP]");
    };;
    if(NULL==FP->USER32.PeekMessageW){ 
        makewind_Halt("[PM]");
    };;

} //[makewind_AssertPeekFunctionExists]//

BOOL_i32_4B
makewind_TakeOrLookMessage( 
/**/LPMSG dont_prefix_message_with_and_symbol
,   int take_the_message
){

    makewind_AssertPeekFunctionExists();

    struct_gleb_SWIN_FUNCTION_POINTERS*
    FP = &(makewind_function_pointers);

    UINT_u32_4B look;
    UINT_u32_4B take;
    UINT_u32_4B look_or_take;

    look = FP->USER32.DATA.pm_noremove;
    take = FP->USER32.DATA.pm_remove;
    look_or_take =(777);

    if( take_the_message > 0 ){
        look_or_take = take;
    }else
    if( 0 == take_the_message ){
        look_or_take = look;
    }else{
        makewind_Halt("[Exp:Pos|Or|Zero]");
    };;

    BOOL_i32_4B ret =(
    FP->USER32.PeekMessageW(
    /**/dont_prefix_message_with_and_symbol
    ,   NULL
    ,   0
    ,   0
    ,   look_or_take
    ));;

    return( ret );

} //[makewind_TakeOrLookMessage]//
BOOL_i32_4B
makewind_LookMessage(
    LPMSG msg
){
    BOOL_i32_4B ret;
    const int look = 0;
    ret=makewind_TakeOrLookMessage(msg,look);
    return( ret );
} //[makewind_LookMessage]//
BOOL_i32_4B
makewind_TakeMessage(
    LPMSG msg
){
    BOOL_i32_4B ret;
    const int take = 1;
    ret=makewind_TakeOrLookMessage(msg,take);
    return( ret );
} //[makewind_TakeMessage]//

//|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|//
//| Since you are discussing threads here,     |//
//| you are aware that GL commands can only    |//
//| be issued from a thread that has an        |//
//| active GL context,correct? And that a      |//
//| context can only be active in 0 or 1       |//
//| threads at a time. If you ever tried to    |//
//| issue commands from a different thread     |//
//| than the one that created your context,    |//
//| and you do not understand this then        |//
//| confusing run-time behvior would ensue;    |//
//| multi-threading is fine in GL,but you      |//
//| have to mind which threads have active     |//
//| contexts.                                  |//
//| stackoverflow.com/questions/21685932/      |//
//|____________________________________________|//
//# Might want to call update here by          #//
//# adding a render update callback?           #//
//# That would get it to fire during WM_PAINT  #//
//# AND get it on same thread, alleviating     #//
//# two possible problems.                     #//
MSG_48B
makewind_WindowLoop(
    v_HWND Hw
){

    struct makewind_functions_USER32*
    U32F = &(
        makewind_function_pointers
       .USER32
    );;

    struct makewind_data_USER32* 
    U32DATA = &( U32F -> DATA);

    int sw_show = U32DATA -> sw_show;
    U32F ->  ShowWindow(  Hw,sw_show); 
    U32F ->  UpdateWindow(Hw        ); 
    U32F ->  SetFocus(    Hw        );

    UINT_u32_4B          wm_quit     ;                
    wm_quit = U32DATA -> wm_quit     ;

    MSG_48B M;
    makewind_LookMessage( &M );
    while(
        M.message
        !=
        wm_quit
    ){
        if( makewind_TakeMessage(    &M )){
            U32F -> TranslateMessage( &M );
            U32F -> DispatchMessageW( &M );
        };;

    };;

    MAKEWIND
    .window_just_closed = ('t'|'r'|'u'|'e');

    //# [HACK]:Sleep a bit so other threads    #//
    //#        see "window_just_closed" update.#//
    //# You really should use a proper mutex.  #//
    Sleep(64);

    return( M );
} //[makewind_WindowLoop]//


void
makewind_MakeWindowCompatibleWith_GL(
    v_HWND  Hw
){

    struct_gleb_SWIN_FUNCTION_POINTERS*
    FP = &(makewind_function_pointers);

    // - // - // - // - // - // - // - // - //

    struct makewind_PW_WINDOWS*
    W32 = &(
        MAKEWIND.PW.W32
    );;

    HDC 
    window_device_context =(
        FP->USER32.GetWindowDC( Hw )
    );;
    int
    pixel_format_number=(
        FP->GDI32.ChoosePixelFormat(
            window_device_context
        , &( W32 -> pixel_format_descriptor )
        )
    );;
    BOOL 
    setting_pixel_format_worked=(
    FP->GDI32.SetPixelFormat(
    /**/  window_device_context
    ,     pixel_format_number
    ,   &( W32 -> pixel_format_descriptor )
    ));;
    if( setting_pixel_format_worked ){
        //: printf("[SPF:OK]\n");
    }else{
        makewind_Halt("[SPF:FAIL]\n");
    };;

    MAKEWIND.PW.W32
    .window_device_context=(
        window_device_context
    );;

} //[makewind_MakeWindowCompatibleWith_GL]//

//: typedef UINT_PTR WPARAM;
//: typedef unsigned (64bit?int64:int) UINT_PTR
//: Call this function on a separate thread!
WPARAM_u64_8B 
makewind_OPEN_WINDOW_LOOP_FOREVER(
    //:UNICODE_STRING
    c_LPCWSTR_b16_2B 
    unique_window_name
){
    struct_gleb_SWIN_FUNCTION_POINTERS*
    FP = &(makewind_function_pointers);

    v_HMODULE 
    hin=(
        FP -> KERNEL32
        .GetModuleHandleW(
            NULL
        )
    );;

    if(NULL==hin){
        makewind_Halt(
            "[FailedToGetModuleHandle]"
        );;
    };;

    //:FreeConsole();

    struct makewind_data_USER32* 
    U32DATA = &( FP->USER32.DATA);

    v_HWND   Hw;
    MSG_48B      Msg;

    if(!

        makewind_RegisterWindow(
            hin
        ,   unique_window_name
        )

    ){ 

        makewind_Alert(
            "[FailedToRegisterWindow]"
        );;
        return 0; 

    };;

    int X   = MAKEWIND.X   ;
    int Y   = MAKEWIND.Y   ;
    int WID = MAKEWIND.WID ;
    int HIG = MAKEWIND.HIG ;

    Hw=FP->USER32.CreateWindowExW(
        //: dwExStyle   (EXT-窓style)
    /**/U32DATA -> ws_ex_topmost 

        //: lpClassName (窓class    )
    ,   unique_window_name    

        //: lpWindowName(窓titlebar )
    ,   L"[GLEB_TITLE_BAR](題圌)"       

        //: (窓style)
    ,   (
            U32DATA -> ws_overlappedwindow  | 
            U32DATA -> cs_owndc             |
        0)

        //: x,y,w,h
    ,   X,Y,WID,HIG       

        //: hWndParent(parent窓)
    ,   FP->USER32.GetDesktopWindow() 

        //: hMenu(HandleToMenu)
    ,   NULL        

        //: hInstance(柯to例)
    ,   hin                

        //: lpParam( ??? )
    ,   NULL               
    );;
    if(Hw==NULL){
        makewind_Halt("[WindowCreateFail]");
        return 0;
    };;

    //:Store the handle to window in global state:
    MAKEWIND.PW.W32.handle_to_window=Hw;

    //:Modifications to make window opengl
    //:compatible:
    //////////////////////////////////////////////
    makewind_MakeWindowCompatibleWith_GL(
        Hw
    );;

    //|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯MC|//
    //!PUT AFTER device context has been     MC!//
    //!set, or your device context fetching  MC!//
    //!function waiting on this flag to be   MC!//
    //!set in this thread will end up        MC!//
    //!with a NULL device context.           MC!//
    //!Speaking Of:                          MC!//
    //!MAKEWIND_GetWindowDeviceContext();   MC!//
    MAKEWIND                //|MC|//
    .window_created=1;                    //|MC|//
    //|______________________________________MC|//

    //////////////////////////////////////////////

    Msg = makewind_WindowLoop( Hw );

    return Msg.wParam;
} //[makewind_OPEN_WINDOW_LOOP_FOREVER]//


void
makewind_ForgotToInitWindowSize(){

    makewind_Alert(
        "[You_Forgot_To_Init_Window_Size]"
    );;

} //[makewind_ForgotToInitWindowSize]//

//:Change window dimensions if they
//:are NOT okay.
int
makewind_ChangeWinDimsIfNotOkay(){

    struct_makewind_global_state*
    GS = &(MAKEWIND);

    int window_size_changed = 0;

    if( 
        0 >= GS -> X   &&
        0 >= GS -> Y   &&
        0 >= GS -> WID &&
        0 >= GS -> HIG &&
    1){
        makewind_ForgotToInitWindowSize();

        GS -> X   =  0;
        GS -> Y   =  0;
        GS -> WID = 1024;
        GS -> HIG = 64;
        window_size_changed=1;
    }else
    if( 
        0 >= GS -> WID || 
        0 >= GS -> HIG ||
    0){
        printf(
            "[XY Set, but window]\n"
            "[size not__________]\n"
        );;

        if( GS -> WID <= 0 ){
            printf("[ForgotToSet:WID]\n");
            GS -> WID = 1024;
            window_size_changed=2;
        };; 
        if( GS -> HIG <= 0 ){
            printf("[ForgotToSet:HIG]\n");
            GS -> HIG =  128;
            window_size_changed=3;
        };;
    };;

    return( window_size_changed );
} //[makewind_ChangeWinDimsIfNotOkay]//

//|WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|//
//| Section:WINDOW_CODE:end -------------------|//
//- 〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓 -//


//| Section:MULTI_THREADING_CODE:beg __________|//
//|MCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMC|//
                                          //|MC|//
void                                      //|MC|//
makewind_PrintCustomThreadData(          //|MC|//
                                          //|MC|//
    v_HINSTANCE custom_data               //|MC|//
                                          //|MC|//
){                                        //|MC|//
                                          //|MC|//
    struct_makewind_global_state*        //|MC|//
    GS = &(MAKEWIND);       //|MC|//
                                          //|MC|//
    //!Both will print the same thing:       MC!//
    ///////////////////////////////////// //|MC|//
    printf(                            // //|MC|//
        "[PARAMS]:( %d, %d )\n"        // //|MC|//
    ,   ((makewind_PMYDATA)           // //|MC|//
        GS->PW.W32.custom_data)->val1  // //|MC|//
                                       // //|MC|//
    ,   ((makewind_PMYDATA)           // //|MC|//
        GS->PW.W32.custom_data)->val2  // //|MC|//
    );                                 // //|MC|//
                                       // //|MC|//
    printf(                            // //|MC|//
        "[PARAMS]:( %d, %d )\n"        // //|MC|//
    ,   ((makewind_PMYDATA)           // //|MC|//
        custom_data)->val1             // //|MC|//
                                       // //|MC|//
    ,   ((makewind_PMYDATA)           // //|MC|//
        custom_data)->val2             // //|MC|//
    );                                 // //|MC|//
    ///////////////////////////////////// //|MC|//
                                          //|MC|//
} //[makewind_PrintCustomThreadData]//   //|MC|//
                                          //|MC|//
DWORD_u32_4B WINAPI                       //|MC|//
makewind_THREAD_FUNCTION(                //|MC|//
                                          //|MC|//
    v_HINSTANCE  custom_data              //|MC|//
                                          //|MC|//
){                                        //|MC|//
    makewind_PrintCustomThreadData(      //|MC|//
        custom_data                       //|MC|//
    );;                                   //|MC|//
                                          //|MC|//
    //!UNICODE_STRING                        MC!//
    c_LPCWSTR_b16_2B                      //|MC|//
    unique_window_name=(                  //|MC|//
        L"MAKEWIND_UNIQUE_WINDOW_NAME"   //|MC|//
    );;                                   //|MC|//
    makewind_OPEN_WINDOW_LOOP_FOREVER(   //|MC|//
        unique_window_name                //|MC|//
    );;                                   //|MC|//
                                          //|MC|//
    return 0;                             //|MC|//
} //[makewind_THREAD_FUNCTION]//         //|MC|//
                                          //|MC|//
void                                      //|MC|//
makewind_AssertThreadCreated(){          //|MC|//
    struct_makewind_global_state*        //|MC|//
    GS = &(MAKEWIND);       //|MC|//
                                          //|MC|//
    //!If thread NULL, creation failed:      MC!//
    if(                                   //|MC|//
        NULL                              //|MC|//
        ==                                //|MC|//
        GS->PW.W32.platform_window_thread //|MC|//
    ){                                    //|MC|//
        printf(                           //|MC|//
            "[GLEB:THREAD_CREATE_FAIL]\n" //|MC|//
        );;                               //|MC|//
        fflush(stdout);                   //|MC|//
        exit( 666 );                      //|MC|//
    };;                                   //|MC|//
} //[makewind_AssertThreadCreated]//     //|MC|//
                                          //|MC|//
void                                      //|MC|//
makewind_CreateThread(){                 //|MC|//
                                          //|MC|//
    struct_makewind_global_state*        //|MC|//
    GS = &(MAKEWIND);       //|MC|//
                                          //|MC|//
    struct_gleb_SWIN_FUNCTION_POINTERS*   //|MC|//
    FP = &(makewind_function_pointers);  //|MC|//
                                          //|MC|//
    struct makewind_functions_KERNEL32*  //|MC|//
    K32F = &(FP -> KERNEL32);             //|MC|//
                                          //|MC|//
    if(NULL==K32F -> HeapAlloc){          //|MC|//
        makewind_NULFUN(                 //|MC|//
            "[HeapAlloc]"                 //|MC|//
        );;                               //|MC|//
    };;                                   //|MC|//
    if(NULL==K32F -> GetProcessHeap){     //|MC|//
        makewind_NULFUN(                 //|MC|//
            "[GetProcessHeap]"            //|MC|//
        );;                               //|MC|//
    };;                                   //|MC|//
                                          //|MC|//
    v_HANDLE                              //|MC|//
    process_heap=(                        //|MC|//
        FP->KERNEL32.GetProcessHeap()     //|MC|//
    );;if(NULL==process_heap){            //|MC|//
        makewind_Halt("process_heap");   //|MC|//
    };;                                   //|MC|//
                                          //|MC|//
    //!Allocate memory for thread data.      MC!//
    GS->PW.W32.custom_data =(             //|MC|//
        (makewind_PMYDATA)               //|MC|//
        FP->KERNEL32.HeapAlloc(           //|MC|//
                                          //|MC|//
            process_heap                  //|MC|//
                                          //|MC|//
        ,   FP->KERNEL32.DATA             //|MC|//
           .heap_zero_memory              //|MC|//
                                          //|MC|//
        ,   sizeof(makewind_MYDATA)      //|MC|//
                                          //|MC|//
        )                                 //|MC|//
    );                                    //|MC|//
                                          //|MC|//
    //|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯//|MC|//
    //! System if out of memory, you will    MC!//
    //! be unable to print error message.    MC!//
    //! But what about error code?           MC!//
    //|___________________________________//|MC|//
    if( GS->PW.W32.custom_data == NULL ){ //|MC|//
        exit( 9873 );                     //|MC|//
    };;                                   //|MC|//
                                          //|MC|//
    //! Set Some Custom Data           !////|MC|//
    GS->PW.W32.custom_data->val1 = 333;   //|MC|//
    GS->PW.W32.custom_data->val2 = 777;   //|MC|//
                                          //|MC|//
    if(NULL==FP->KERNEL32.CreateThread){  //|MC|//
        makewind_NULFUN("CreateThread"); //|MC|//
    };;                                   //|MC|//
                                          //|MC|//
    //|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|////|MC|//
    //| Create the thread to begin     |////|MC|//
    //| execution on its own.          |////|MC|//
    //|________________________________|////|MC|//
    GS->PW.W32.platform_window_thread=(   //|MC|//
    FP->KERNEL32.CreateThread( //|¯¯¯¯¯|////|MC|//
    //+ default_security ------------_1+////|MC|//
    /**/NULL                      //[01]////|MC|//
                                  //|  |////|MC|//
    //+ default_stack_size ----------_2+////|MC|//
    ,   0                         //[02]////|MC|//
                                  //|  |////|MC|//
    //+ lpStartAddress --------------_3+////|MC|//
    ,   makewind_THREAD_FUNCTION //[03]////|MC|//
                                  //|  |////|MC|//
    //+ thread_func_arg -------------_4+////|MC|//
    ,   GS->PW.W32.custom_data    //[04]////|MC|//
                                  //|  |////|MC|//
    //+ use default creation flags---_5+////|MC|//
    ,   0                         //[05]////|MC|//
                                  //|  |////|MC|//
    //+ Output_Param ----------------_6+////|MC|//
    ,   &GS->PW.W32.thread_id     //[06]////|MC|//
    ));;//|____________________________|////|MC|//
                                          //|MC|//
} //[makewind_CreateThread]//            //|MC|//
                                          //|MC|//
//|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯ MC|//
//! If the user of this library improperly   MC!//
//! set the window size (or forgot)          MC!//
//! before calling the intialize function,   MC!//
//! we will warn the user with an alert      MC!//
//! box and attempt to fix the problem.      MC!//
//|-  --  --  --  --  --  --  --  --  --  -- MC|//
void                                      //|MC|//
makewind_CorrectWindowIfNeeded(){        //|MC|//
                                          //|MC|//
    int r=0;                              //|MC|//
    r=makewind_ChangeWinDimsIfNotOkay(); //|MC|//
    r=makewind_ChangeWinDimsIfNotOkay(); //|MC|//
    if( 0 != r ){                         //|MC|//
        makewind_Halt(                   //|MC|//
            "[WindowDimFixFail]"          //|MC|//
        );;                               //|MC|//
    };;                                   //|MC|//
                                          //|MC|//
} //[makewind_CorrectWindowIfNeeded]//   //|MC|//
                                          //|MC|//
void MAKEWIND_Init(){                    //|MC|//
                                          //|MC|//

    MAKEWIND
    .init_called = 1;

    makewind_InitGlobalStateContainer(); //|MC|//

    //! NEAR_TOP:                      !////|MC|//
    makewind_AssertCorrectSizesOfTypes();//|MC|//
                                          //|MC|//
    //! NEAR_TOP:                      !////|MC|//
    //! MessageBox(...)                !////|MC|//
    //! loaded from User32.dll.        !////|MC|//
    init_gleb_SWIN_FUNCTION_POINTERS();   //|MC|//
                                          //|MC|//
    makewind_CorrectWindowIfNeeded();    //|MC|//
                                          //|MC|//
    makewind_CreateThread();             //|MC|//
    makewind_AssertThreadCreated();      //|MC|//
                                         

    MAKEWIND
    .init_finished = 1;

} //[MAKEWIND_Init]//                    //|MC|//
void MAKEWIND_Initialize(){              //|MC|//
     MAKEWIND_Init();                    //|MC|//
} //[MAKEWIND_Initialize]//              //|MC|//
                                          //|MC|//
void                                      //|MC|//
makewind_HeapFreeFail(){                 //|MC|//
                                          //|MC|//
    printf(                               //|MC|//
        "[GLEBSWIN:HeapFreeFail]\n"       //|MC|//
    );;                                   //|MC|//
                                          //|MC|//
    fflush( stdout );                     //|MC|//
    exit(666);                            //|MC|//
                                          //|MC|//
}                                         //|MC|//
                                          //|MC|//
//! af=="assert function"              !////|MC|//
void                                      //|MC|//
makewind_af_HeapFreeSuccess(             //|MC|//
    int was_heap_free_success             //|MC|//
){                                        //|MC|//
    if(0==was_heap_free_success){         //|MC|//
                                          //|MC|//
        makewind_HeapFreeFail();         //|MC|//
                                          //|MC|//
    }                                     //|MC|//
                                          //|MC|//
}                                         //|MC|//
                                          //|MC|//
void                                      //|MC|//
makewind_FreeCustomDataIfExists(){       //|MC|//
                                          //|MC|//
    struct_makewind_global_state*        //|MC|//
    GS = &(MAKEWIND);       //|MC|//
                                          //|MC|//
    if( NULL == GS->PW.W32.custom_data ){ //|MC|//
        return;                           //|MC|//
    };;                                   //|MC|//
                                          //|MC|//
    struct_gleb_SWIN_FUNCTION_POINTERS*   //|MC|//
    FP = &(makewind_function_pointers);  //|MC|//
                                          //|MC|//
    //|--------------------------------|////|MC|//
                                          //|MC|//
    if(NULL==FP->KERNEL32.HeapFree){      //|MC|//
        printf(                           //|MC|//
            "[ERROR:4gotFetch:HeapFree]\n"//|MC|//
        );;                               //|MC|//
        fflush( stdout );                 //|MC|//
        exit( 666 );                      //|MC|//
    };;                                   //|MC|//
                                          //|MC|//
    //|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|////|MC|//
    //|Kernel32.dll                    |////|MC|//
    //|Frees a memory block alloced    |////|MC|//
    //|from a heap by the HeapAlloc    |////|MC|//
    //|or HeapReAlloc function.        |////|MC|//
    BOOL_i32_4B                   //|  |////|MC|//
    was_heap_free_success;        //|  |////|MC|//
    was_heap_free_success=(       //|  |////|MC|//
    FP->KERNEL32.HeapFree(        //|  |////|MC|//
                                  //|  |////|MC|//
        //|Heap where memory block     |////|MC|//
        //|you want to free lives.     |////|MC|//
    /**/FP->KERNEL32              //|  |////|MC|//
       .GetProcessHeap()          //|  |////|MC|//
                                  //|  |////|MC|//
        //|DWORD dwFlags:              |////|MC|//
        //|(heap free opts)            |////|MC|//
    ,   0                         //|  |////|MC|//
                                  //|  |////|MC|//
        //|Pointer to memory           |////|MC|//
        //|block to free:              |////|MC|//
    ,   GS->PW.W32.custom_data    //|  |////|MC|//
    ));;                          //|  |////|MC|//
                                  //|  |////|MC|//
    makewind_af_HeapFreeSuccess( //|  |////|MC|//
        was_heap_free_success     //|  |////|MC|//
    );;                           //|  |////|MC|//
                                  //|  |////|MC|//
    //| Ensure address is              |////|MC|//
    //| NOT reused.                    |////|MC|//
    GS->PW.W32.custom_data = NULL;//|  |////|MC|//
                                  //|  |////|MC|//
    //|________________________________|////|MC|//
                                          //|MC|//
    makewind_OK("[CustomDataFreed]");    //|MC|//
                                          //|MC|//
} //[makewind_FreeCustomDataIfExists]//  //|MC|//
                                          //|MC|//
//! Close window thread and free       !////|MC|//
//! custom data                        !////|MC|//
void                                      //|MC|//
makewind_ShutWinThread_FreeData(){       //|MC|//
                                          //|MC|//
    struct_makewind_global_state*        //|MC|//
    GS = &(MAKEWIND);       //|MC|//
                                          //|MC|//
    struct_gleb_SWIN_FUNCTION_POINTERS*   //|MC|//
    FP = &(makewind_function_pointers);  //|MC|//
                                          //|MC|//
    //|-  --  --  --  --  --  --  --  --  -- MC|//
                                          //|MC|//
    //!Close all thread handles and    !////|MC|//
    //!free memory allocations.        !////|MC|//
    BOOL_i32_4B ok = 0;                   //|MC|//
                                          //|MC|//
    if(NULL==FP->KERNEL32.CloseHandle){   //|MC|//
        makewind_Halt(                   //|MC|//
            "[null:CloseHandle]"          //|MC|//
        );;                               //|MC|//
    };;                                   //|MC|//
    ok = FP->KERNEL32.CloseHandle(        //|MC|//
        GS->PW.W32.platform_window_thread //|MC|//
    );;if( 0 == ok ){                     //|MC|//
        makewind_Halt(                   //|MC|//
            "[CloseHandleFail]"           //|MC|//
        );;                               //|MC|//
    };;                                   //|MC|//
                                          //|MC|//
    makewind_FreeCustomDataIfExists();   //|MC|//
                                          //|MC|//
} //[function]//                          //|MC|//
                                          //|MC|//
                                          //|MC|//
//!fe: "function exists"               !////|MC|//
void                                      //|MC|//
makewind_fe_WaitForSingleObject(){       //|MC|//
                                          //|MC|//
    struct_gleb_SWIN_FUNCTION_POINTERS*   //|MC|//
    FP = &(makewind_function_pointers);  //|MC|//
                                          //|MC|//
    if(                                   //|MC|//
        NULL                              //|MC|//
        ==                                //|MC|//
        FP->KERNEL32                      //|MC|//
        .WaitForSingleObject              //|MC|//
    ){                                    //|MC|//
        makewind_Halt("[Null:WFSO:PTR]");//|MC|//
    };;                                   //|MC|//
                                          //|MC|//
} //[makewind_fe_WaitForSingleObject]//  //|MC|//
                                          //|MC|//
void                                      //|MC|//
makewind_WaitUntilWindowClosed(){        //|MC|//
                                          //|MC|//
    struct_makewind_global_state*        //|MC|//
    GS = &(MAKEWIND);       //|MC|//
                                          //|MC|//
    struct_gleb_SWIN_FUNCTION_POINTERS*   //|MC|//
    FP = &(makewind_function_pointers);  //|MC|//
                                          //|MC|//
    makewind_fe_WaitForSingleObject();   //|MC|//
                                          //|MC|//
    //!Wait until all threads          !////|MC|//
    //!have terminated.                !////|MC|//
    struct makewind_data_KERNEL32*       //|MC|//
    K32D = &(                             //|MC|//
        FP->KERNEL32.DATA                 //|MC|//
    );;                                   //|MC|//
                                          //|MC|//
    DWORD_u32_4B dont_fail_me=(           //|MC|//
    FP->KERNEL32.WaitForSingleObject(     //|MC|//
    /**/GS->PW.W32.platform_window_thread //|MC|//
    ,       K32D -> infinite              //|MC|//
    ));;                                  //|MC|//
    if( K32D -> wait_failed               //|MC|//
        ==                                //|MC|//
        dont_fail_me                      //|MC|//
    ){                                    //|MC|//
                                          //|MC|//
        printf(                           //|MC|//
            "[ThreadedWindowWaitFail]"    //|MC|//
        );;                               //|MC|//
                                          //|MC|//
    }else{                                //|MC|//
                                          //|MC|//
        makewind_OK(                     //|MC|//
            "[ThreadedWindowClosed]"      //|MC|//
        );;                               //|MC|//
                                          //|MC|//
    };;                                   //|MC|//
                                          //|MC|//
}                                         //|MC|//
                                          //|MC|//
//|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|//
//! A blocking call that loops forever.      MC!//
//! Put it outside of your main loop to      MC!//
//! make sure program does not exit until    MC!//
//! window is closed.                        MC!//
//!                                          MC!//
//! Do NOT put before main loop in code.     MC!//
//!                                          MC!//
//! Wait on:                                 MC!//
//! SWIN(SilkWindow/ThreadedWindow)          MC!//
//|-  --  --  --  --  --  --  --  --  --  --  -|//
void MAKEWIND_Wait(){                    //|MC|//
                                          //|MC|//
    makewind_WaitUntilWindowClosed();    //|MC|//
    makewind_ShutWinThread_FreeData();   //|MC|//
                                          //|MC|//
} //[MAKEWIND_Wait]//                    //|MC|//
void                                      //|MC|//
MAKEWIND_WaitForUserToCloseWindow(){     //|MC|//
    MAKEWIND_Wait();                     //|MC|//
}                                         //|MC|//
//|MCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMC|//
//| Section:MULTI_THREADING_CODE:end ¯¯¯¯¯¯¯¯¯¯|//



void
makewind_WaitHereUntilWindowExists(){

    struct_makewind_global_state*
    GS = &(MAKEWIND);

    int hackish_timer = 0;
    while( GS -> window_created <= 0 ){

        hackish_timer++;
        if( hackish_timer > 1024*1024*32 ){
            makewind_OK(
                "[Waiting_On_Window_Creation]"
            );;
            fflush( stdout );
            hackish_timer = 0;
        };; 
    };;

    makewind_OK(
        "[DONE_WAITING_ON_WINDOW_CREATION]"
    );;fflush(stdout);

} //[makewind_WaitHereUntilWindowExists]//


//|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|//
//| Added: DATE[2019_06_14]                    |//
//| Currently trying to get triangle to        |//
//| show up on screen in GA.H of GAKU.H        |//
//| project. Think problem is:                 |//
//| 1. A threading problem.                    |//
//| 2. Screwed up opengl drawing code.         |//
void*                                       //||//
MAKEWIND_GetWinDC_ExistsNoWait(){          //||//
    if(                                     //||//
        NULL==MAKEWIND.PW.W32 //||//
        .window_device_context              //||//
    ){                                      //||//
        makewind_Halt(                     //||//
            "[FAIL:GetWinDC_ExistsNoWait]"  //||//
        );;                                 //||//
    };;                                     //||//
    return( MAKEWIND.PW.W32   //||//
            .window_device_context );       //||//
} //[MAKEWIND_GetWinDC_ExistsNoWait]//     //||//
//|____________________________________________|//

//:Returns a (void*) instead of an HDC because:
//: 1. Want to get rid of windows.h eventually.
//: 2. Want to make sure that if this library
//:    is in a project that uses windows.h,
//:    it can still compile.
void*
MAKEWIND_GetWinDC(){
    struct_makewind_global_state*
    GS = &(MAKEWIND);
    

    //:If you forget to initialize,
    //:then the waiting on window creation
    //:loop will execute forever because
    //:no window creation is happening
    //:on a different thread.
    if( 0 == GS -> init_called ){
        makewind_Halt(
            "[YouForgot:MAKEWIND_Init()!]"
        );;
    };;

    makewind_WaitHereUntilWindowExists();


    if( 0 == 
        GS -> PW.W32
        .window_device_context
    ){
        makewind_Halt(
            "[WindowWaitMechanismFailed]"
        );;
    };;


    HDC ret = GS -> PW.W32.window_device_context;
    return( (void*)ret );
    
} //[MAKEWIND_GetWindowDeviceContext]//
void* MAKEWIND_GetWindowDeviceContext(){
    return(
        MAKEWIND_GetWinDC()
    );;
}
int 
MAKEWIND_Demo( void ){
    printf(
        "[BEG:MAKEWIND_Demonstration]\n"
    );;
    fflush(stdout);
    
    MAKEWIND.X   = 22  ;
    MAKEWIND.Y   = 22  ;
    MAKEWIND.WID = 1024;
    MAKEWIND.HIG = 512 ;


    //:This creates our window:
    MAKEWIND_Init();
   
    //:This gets our window's device
    //:context, which can be used to
    //:create OpenGL context.
    //:GL=="Graphics Library"
    MAKEWIND_GetWinDC();

    int X   = MAKEWIND_GetClient_X  ();
    int Y   = MAKEWIND_GetClient_Y  ();
    int WID = MAKEWIND_GetClient_WID();
    int HIG = MAKEWIND_GetClient_HIG();
    printf(
    /**/"[CLIENT_DIMS]\n"
    /**/" X  :%d\n"
    /**/" Y  :%d\n"
    /**/" WID:%d\n"
    /**/" HIG:%d\n"
    ,X,Y,WID,HIG
    );;

    //: Uncomment this line if you want
    //: to observe proof that the window's
    //: loop is off in another thread.
    //: while( 1 ){ };
   
    //:Put this after your game loop
    //:so that program does not exit
    //:until window is closed.
    MAKEWIND_Wait();

    printf(
        "[END:MAKEWIND_Demonstration]\n"
    );;
    fflush(stdout);

    return 0;
} //[main]//
int
MAKEWIND_Demonstration( void ){
    return(
        MAKEWIND_Demo()
    );;
} 


//|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|//
//| We will use this for testing if game loop  |//
//| should still be running. Do NOT create     |//
//| a function called "IsWindowOpen".          |//
//| We need to be more pedantic than that.     |//
//|-  --  --  --  --  --  --  --  --  --  --  -|//
int                                         //||//
MAKEWIND_IsWindowStillOpen( void ){        //||//
                                            //||//
    int is_window_still_open = (0-666);     //||//
                                            //||//
    if(                                     //||//
        MAKEWIND              //||//
        .window_created                     //||//
        <= 0                                //||//
    ){                                      //||//
        makewind_Halt(                     //||//
            "[ObjectionYourHonor________]\n"//||//
            "[TheStatementAssumesAWindow]\n"//||//
            "[WasOpenToBeginWith________]\n"//||//
        );;                                 //||//
    };;                                     //||//
                                            //||//
    if(                                     //||//
        MAKEWIND              //||//
        .window_just_closed                 //||//
        > 0                                 //||//
    ){                                      //||//
        is_window_still_open = 0;           //||//
    }else{                                  //||//
        is_window_still_open = 1;           //||//
    };;                                     //||//
                                            //||//
    if(                                     //||//
        is_window_still_open != 0 &&        //||//
        is_window_still_open != 1 &&        //||//
    1){                                     //||//
        makewind_Halt("[Exp:(1|0):IWSO]"); //||//
    };;                                     //||//
                                            //||//
    return( is_window_still_open );         //||//
                                            //||//
}                                           //||//
//|____________________________________________|//

int
MAKEWIND_GetClient_X(){

    RECT r; //:TempRect
    v_HWND handle_to_window=(
           MAKEWIND.PW.W32.handle_to_window
    );;

    makewind_function_pointers
    .USER32
    .GetClientRect(
    /**/   handle_to_window
    ,    &(r)
    );;

    int X = r.left;
    return( X );
}
int
MAKEWIND_GetClient_Y(){
    RECT r; //:TempRect
    v_HWND handle_to_window=(
           MAKEWIND.PW.W32.handle_to_window
    );;

    makewind_function_pointers
    .USER32
    .GetClientRect(
    /**/   handle_to_window
    ,    &(r)
    );;

    int Y = r.top;
    return( Y );
}
int
MAKEWIND_GetClient_WID(){
    RECT r; //:TempRect
    v_HWND handle_to_window=(
           MAKEWIND.PW.W32.handle_to_window
    );;

    makewind_function_pointers
    .USER32
    .GetClientRect(
    /**/   handle_to_window
    ,    &(r)
    );;

    //:No need for +1 because right exclusive.
    int WID = ( r.right - r.left ) + 0;
    return( WID );
}
int
MAKEWIND_GetClient_HIG(){
    RECT r; //:TempRect
    v_HWND handle_to_window=(
           MAKEWIND.PW.W32.handle_to_window
    );;

    makewind_function_pointers
    .USER32
    .GetClientRect(
    /**/   handle_to_window
    ,    &(r)
    );;

    //:No need for +1 because bottom exclusive.
    int HIG =( r.bottom - r.top ) + 0;
    return( HIG );
}



//: For parallel processing and keeping the
//: window loop responsive, it makes more sense
//: to signal with a mutex that can be checked.
//////////////////////////////////////////////////////////////
//-  //:Because I think code is not rendering because      -//
//-  //:the calls are on the wrong thread:                 -//
//-  //:I MIGHT end up not using this, but need to         -//
//-  //:troubleshoot why opengl is not showing             -//
//-  //:anything.                                          -//
//-  void                                                  -//
//-  MAKEWIND_PutRenderTickFunction(                      -//
//-      void(*function_name)( void )                      -//
//-  ){                                                    -//
//-                                                        -//
//-  /*01*/  #define C_B MAKEWIND.OPTIONAL_CALLBACKS      -//
//-  /*02*/  #define X_X makewind_Halt                    -//
//-  /*03*/  #define HAS render_tick_function_has          -//
//-  /*04*/  #define FUN render_tick_function              -//
//-  /*05*/  #define M_1 "[RenderTickFuncAlreadySet]"      -//
//-  /*06*/  #define M_2 "[Input_RTF_NULL]"                -//
//-                                                        -//
//-      if(C_B.HAS || (C_B.FUN!=NULL)){ X_X( M_1 );};     -//
//-      if(NULL==function_name){        X_X( M_2 );};     -//
//-      C_B.FUN=(function_name);                          -//
//-      C_B.HAS=1;                                        -//
//-                                                        -//
//-  /*01*/  #undef C_B  //|01 ----------------- 01 |//    -//
//-  /*02*/  #undef X_X  //|02 ----------------- 02 |//    -//
//-  /*03*/  #undef HAS  //|03 ----------------- 03 |//    -//
//-  /*04*/  #undef FUN  //|04 ----------------- 04 |//    -//
//-  /*05*/  #undef M_1  //|05 ----------------- 05 |//    -//
//-  /*06*/  #undef M_2  //|06 ----------------- 06 |//    -//
//-                                                        -//
//-  }                                                     -//
//-                                                        -//
//-  void                                                  -//
//-  MAKEWIND_PutResizeFunction(                          -//
//-      void(*function_name)( void )                      -//
//-  ){                                                    -//
//-                                                        -//
//-  /*01*/  #define C_B MAKEWIND.OPTIONAL_CALLBACKS      -//
//-  /*02*/  #define X_X makewind_Halt                    -//
//-  /*03*/  #define HAS resize_function_has               -//
//-  /*04*/  #define FUN resize_function                   -//
//-  /*05*/  #define M_1 "[ResizeFuncAlreadySet]"          -//
//-  /*06*/  #define M_2 "[PRF:NullInput]"                 -//
//-                                                        -//
//-      if(C_B.HAS || (C_B.FUN!=NULL)){ X_X( M_1 );};     -//
//-      if(NULL==function_name){        X_X( M_2 );};     -//
//-      C_B.FUN=(function_name);                          -//
//-      C_B.HAS=1;                                        -//
//-                                                        -//
//-  /*01*/  #undef C_B  //|01 ----------------- 01 |//    -//
//-  /*02*/  #undef X_X  //|02 ----------------- 02 |//    -//
//-  /*03*/  #undef HAS  //|03 ----------------- 03 |//    -//
//-  /*04*/  #undef FUN  //|04 ----------------- 04 |//    -//
//-  /*05*/  #undef M_1  //|05 ----------------- 05 |//    -//
//-  /*06*/  #undef M_2  //|06 ----------------- 06 |//    -//
//-                                                        -//
//-  }                                                     -//
//////////////////////////////////////////////////////////////

void
MAKEWIND_SwapBuffers( void ){

    if(NULL==MAKEWIND.PW.W32
    .window_device_context){

        makewind_Halt(
            "[CantSwapBuffersWithNullDevice]"
        );;

    };;

    makewind_function_pointers
    .GDI32.SwapBuffers(
        MAKEWIND.PW.W32
        .window_device_context
    );;

}

//|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|//
//|PUBLIC Functions:                           |//
//|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _   |//
int   MAKEWIND_Demo(          void );      //||//
int   MAKEWIND_Demonstration( void );      //||//
                                            //||//
void  MAKEWIND_Init(       /**void**/  );  //||//
void  MAKEWIND_Initialize( /**void**/  );  //||//
                                            //||//
void* MAKEWIND_GetWindowDeviceContext();   //||//
void* MAKEWIND_GetWinDC();                 //||//
                                            //||//
void  MAKEWIND_Wait(         /**void**/  );//||//
void  MAKEWIND_WaitForUserToCloseWindow( );//||//
                                            //||//
int   MAKEWIND_IsWindowStillOpen( );       //||//
                                            //||//
//:So we don't have to return "RECT"        //||//
//:Structures, use 4 calls instead of       //||//
//:making "MAKEWIND_GetClientArea"         //||//
int   MAKEWIND_GetClient_X(  );            //||//
int   MAKEWIND_GetClient_Y(  );            //||//
int   MAKEWIND_GetClient_WID();            //||//
int   MAKEWIND_GetClient_HIG();            //||//

void  MAKEWIND_PutRenderTickFunction(
    void(*function_name)( void )
);

void  MAKEWIND_SwapBuffers( void );

//|____________________________________________|//

