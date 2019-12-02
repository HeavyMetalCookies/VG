##################################################
############## SC[ vg_hkmf_2019 ] ################
##################################################
base_name_no_extension="DEMO"
ext="temp_c11" ##Temp_File_Extension
c_v="c11"      ## version of c to compile as

##GLFW (V:\DEPS\GLFW\include\GLFW\glfw3.h )
##Does the following if GLFW_INCLUDE_VULKAN
##is defined. So need to have search directory
##for vulkan folder.
##
##   #if defined(GLFW_INCLUDE_VULKAN)
##   #include <vulkan/vulkan.h>
##   #endif /* Vulkan header */
##

    ## V:/VK_HEAD/include/vulkan/vulkan.h
    path_to_vulkan_folder="V:/VK_HEAD/include/"

    path_to_libglfw3_a="V:\DEPS\GLFW_BUILD_ZOTAC\STEP_02\lib\libglfw3.a"

##Transpile our single source file into english:
##TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT##

    e_n_g_l_i_s_h="VG1.okay_to_delete"
    cp "VG1.H" "$e_n_g_l_i_s_h"

   
    K01="玉星"
    E01="yuxing"

    K02="水"
    E02="FIRE"

    K03="地"
    E03="EARTH"

    K04="木"
    E04="TreeKanji"

    sed -i -e "s/$K01/$E01/g" $e_n_g_l_i_s_h
    sed -i -e "s/$K02/$E02/g" $e_n_g_l_i_s_h
    sed -i -e "s/$K03/$E03/g" $e_n_g_l_i_s_h
    sed -i -e "s/$K04/$E04/g" $e_n_g_l_i_s_h

##TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT##

DEMO_CODE=$(cat << DEMO_CODE_HERE_DOC
//////////////////////////////////////////////////
    #include "$e_n_g_l_i_s_h"                            
                                                 
    int                                          
    main(                                        
        void                                     
    ){                                           
                                                 
        yuxing_Demo();               
                                                 
    }  //                                        
//////////////////////////////////////////////////
DEMO_CODE_HERE_DOC
)

touch $base_name_no_extension.$ext
>     $base_name_no_extension.$ext
echo "$DEMO_CODE" >> $base_name_no_extension.$ext

##################################################
MY_COMMAND_STRING=$(cat << GCC_COMMAND_01
    gcc                                     
    -x c                                    
    -c $base_name_no_extension.$ext          
    -o my_object_file.o  
    -I $path_to_vulkan_folder
    -l $path_to_libglfw3_a
    -l opengl32.dll
    -m64                                    
GCC_COMMAND_01
)                                       
C=$MY_COMMAND_STRING  ############################
C=$C"-Werror        " ## WarningsAreErrors      ##
C=$C"-Wfatal-errors " ## StopAtFirstError       ##
C=$C"-Wpedantic     " ## UseStrictISO_C         ##
C=$C"-Wall          " ## WarnAboutAnyWeirdCode  ##
C=$C"-Wextra        " ## "-Wall" WarningsExtra  ##
C=$C"-std=$c_v      " ## VersionOf_C_ToUse      ##
MY_COMMAND_STRING=$C  ############################

echo $MY_COMMAND_STRING
     $MY_COMMAND_STRING
     
C1=" gcc -o EXE.exe my_object_file.o "    
C2=" ./EXE.exe                       "    
C3=" rm my_object_file.o             "    
C4=" rm EXE.exe                      "  
C5=" rm $base_name_no_extension.$ext  "
$C1 && echo "OK:"$C1 || "FAIL:$C1"
$C2 && echo "OK:"$C2 || "FAIL:$C2"
$C3 && echo "OK:"$C3 || "FAIL:$C3"
$C4 && echo "OK:"$C4 || "FAIL:$C4"
$C5 && echo "OK:"$C5 || "FAIL:$C5"
##################################################
read -p "[END_OF_BUILD_SCRIPT:PressAnyKey]:"
##################################################
############## SC[ vg_hkmf_2019 ] ################
##################################################