

#include<stdlib.h> //:for: malloc(...)
#include<stdlib.h> //:for:   free(...)
#include <stdio.h> //:for: printf(...)

//:WC:Window Creation:
//:WCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWC://



//:WCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWCWC://

void VG03_Init(){
    F01_Init();


    
}//[;]//

int
VG03_Demo( void ){

    printf("[BEG:VG03_DEMO]\n");

    VG03_Init();

    F04_Demo_SingleThreaded();

    printf("[END:VG03_DEMO]\n");

    return( 0 );
}//[;]//

struct VG03_BLUEPRINT{

    int( *Demo )( void );

}VG03={

    .Demo = &( VG03_Demo )

};//[struct]//



