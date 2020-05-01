

exe_SRC="exe._" ## 
EXE_CAT () {

    ##--------------------------------------------------------##

    echo "[INPUTS:1&2]:" $1 $2

    ##--------------------------------------------------------##
    
    part_a="//++++++++++++++++++++++++++++++"
    part_b="+++++++++++++++++++++++++++////{"
    ab_lin=$part_a$part_b

    part_c="//++++++++++++++++++++++++++++++"
    part_d="++++++++++++++++++++++++++++++//"
    cd_lin=$part_c$part_d

    ##--------------------------------------------------------##

    ##Top_Divider:
    echo $cd_lin                  >> $exe_SRC
    echo "//{//+EXE_CAT:BELOW+//:$1" >> $exe_SRC ## }

    ##--------------------------------------------------------##

    ##Actual_Source_File_Content:
    echo $'\n'                    >> $exe_SRC
    cat $1                        >> $exe_SRC
    echo $'\n'                    >> $exe_SRC

    ##--------------------------------------------------------##

    ##Bot_Divider:
    echo "//}"                       >> $exe_SRC ##CODE_FOLD
    echo "//++++EXE_CAT:ABOVE+//:$1" >> $exe_SRC
    echo $cd_lin                     >> $exe_SRC

    ##--------------------------------------------------------##

}
>  $exe_SRC ##ERASE_OLD_FILE_CONTENTS

## Dependencies before any our our library global macros
## so that we don't risk our macros fucking up any library
## code included in the project:
EXE_CAT "./SRC/DEPENDENCIES._"


## Project namespace basically. Undefined in footer.
EXE_CAT "./SRC/PROJECT_PREFIX.DEFINE._" 

## So we don't have to re-create all the function signatures
## we want to use.
EXE_CAT "./SRC/FUNCTION_TYPEDEF_PYRAMID._"

################################################################

##These dependencies should be listed in order of execution:
##You can comment off as may sequential files from the tip,
##And the project should still compile.

    ## ORDER_MATTERS_HERE!

    EXE_CAT "./SRC/MAINLOOP/looptable._"
    EXE_CAT "./SRC/NATIVE/CALLWRAP/LoadLibrary._"
    EXE_CAT "./SRC/NATIVE/CALLWRAP/GetProcAddress._"
    EXE_CAT "./SRC/NATIVE/ping._"
    EXE_CAT "./SRC/NATIVE/WINDOW/creation._"

    ## Any API interop code needs to come AFTER basic setup:
##  EXE_CAT "./SRC/VULKAN/SETUP/main._" ## VK BEFORE CL
    EXE_CAT "./SRC/OPENGL/SETUP/main._" ## GL BEFORE CL
    EXE_CAT "./SRC/OPENCL/SETUP/main._" ## CL AFTER GL & VK


################################################################

EXE_CAT "./MAIN.C11" 


EXE_CAT "./SRC/CHAIN_FILE.UNDEF._"     
EXE_CAT "./SRC/PROJECT_PREFIX.UNDEF._" 



    ##  SC[ hkmf-mini] #########################################
    ## SEE[ hkmf-c11 ] for reference:  #########################
    ############################################################
    gcc                                                        \
        -x c                                                   \
        -c $exe_SRC                                            \
        -o  exe.OBJ                                            \
                                                               \
            -fmax-errors=1                                     \
            -Wpedantic                                         \
            -Wall                                              \
            -Wextra                                            \
                                                               \
            -fstrict-aliasing                                  \
            -Wstrict-aliasing                                  \
                                                               \
            -Werror=vla                                        \
                                                               \
            -D MACRO_COMPILE_ONLY_THIS_FILE_AS_DEMO            \
                                                               \
            -std=c11                                           \
            -m64 ###############################################
                                    ####                    ####
    gcc -o EXE.exe exe.OBJ          ####                    ####
    rm             exe.OBJ          ####                    ####
        ./EXE.exe                  ####                    ####
    rm     EXE.exe                  ####                    ####
                                    ####                    ####
    read -p "[ENTER_TO_EXIT]:"      ####                    ####
    ############################################################