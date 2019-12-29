##################################################
############## SC[ xxxxxxxxxx-sh ] ###############
######## ALSO_SEE[ xxxxxxxxxx-cx ] ###############
##################################################




                LIB_ALL="VG03" 




##################################################
##                                              ##
##      BASH_HELPER_FUNCTIONS                   ##
##################################################
    
    function nl_cat () {

        ##Add newline to dest file.
        printf "\n" >> $2 
        
        ##Add code into dest file.
        cat $1      >> $2

    }

##################################################
##PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP##
                                                    
            ######################### 
            ##  PRJ Specific Code  ##
            #########################

touch "VG03.ALL"  ##Create
    > "VG03.ALL"  ##Clean

################################################################


nl_cat "./W32/DLLL/DLLL.COMSET"     "VG03.ALL"
nl_cat "./W32/DLLL/TARG/W10.X64"    "VG03.ALL"
nl_cat "./W32/DLLL/DLLL.H"          "VG03.ALL" 

################################################################

##Concatted mostly for reference:
#####################################################
printf "\n\n"                           >> "VG03.ALL"
   echo "#define F01_BASH_CONCATTED"    >> "VG03.ALL"
printf "\n\n"                           >> "VG03.ALL"

                           cat "./F.01" >> "VG03.ALL"   

printf "\n\n\n"                         >> "VG03.ALL"
   echo "#undef  F01_BASH_CONCATTED"    >> "VG03.ALL"
printf "\n"                             >> "VG03.ALL"
#####################################################


    nl_cat "./F.02"  "VG03.ALL"
    nl_cat "./F.03"  "VG03.ALL"
    nl_cat "./F.04"  "VG03.ALL"  ## DLL_STRUCTS
    nl_cat "./F.05"  "VG03.ALL"  ## DLL_TYPEDEFS

##Concatted mostly for reference:
#####################################################
printf "\n\n"                           >> "VG03.ALL"
   echo "#define F06_BASH_CONCATTED"    >> "VG03.ALL"
printf "\n\n"                           >> "VG03.ALL"

                           cat "./F.06" >> "VG03.ALL"   

printf "\n\n\n"                         >> "VG03.ALL"
   echo "#undef  F06_BASH_CONCATTED"    >> "VG03.ALL"
printf "\n"                             >> "VG03.ALL"
#####################################################


##Concatted mostly for reference:
#####################################################
printf "\n\n"                           >> "VG03.ALL"
   echo "#define F07_BASH_CONCATTED"    >> "VG03.ALL"
printf "\n\n"                           >> "VG03.ALL"

                           cat "./F.07" >> "VG03.ALL"   

printf "\n\n\n"                         >> "VG03.ALL"
   echo "#undef  F07_BASH_CONCATTED"    >> "VG03.ALL"
printf "\n"                             >> "VG03.ALL"
#####################################################

########################################

    nl_cat "./F.08"     "VG03.ALL"
    nl_cat "./F.09"     "VG03.ALL"
    nl_cat "./F.10"     "VG03.ALL"

########################################

    ##Vulkan Specific Code Begins:

    nl_cat "./F.20"     "VG03.ALL"  ## VULKAN_STRUCTS
    nl_cat "./F.30"     "VG03.ALL"  ## VULKAN_PFN_TYPEDEFS
    nl_cat "./F.35"     "VG03.ALL"  ## STRUCTS_WITH_PFN_MEMBERS
    nl_cat "./F.36"     "VG03.ALL"  ## VALIDLAY_LIST
    nl_cat "./F.37"     "VG03.ALL"  ## INST_EXT_LIST
    nl_cat "./F.40"     "VG03.ALL"  ## VULKAN_TUTORIAL_CODE
 
    nl_cat "./F.50"     "VG03.ALL"  ## RAW_VK_EXT_FUNC_PTRS
    nl_cat "./F.55"     "VG03.ALL"  ## CAS_VK_EXT_FUNC_PTRS
    nl_cat "./F.60"     "VG03.ALL"  ## VULKAN_INIT_CONTINUED
    nl_cat "./F.61"     "VG03.ALL"  ## WIN32_SURFACE

    ## The graphics + compute queue selections
    ## are in PHYDEV_SELECT. That is worthy
    ## of refactor by splitting "F.62" into two files.
    nl_cat "./F.62"     "VG03.ALL"  ## PHYDEV_SELECT
    nl_cat "./F.63"     "VG03.ALL"  ## GET_PRESENT_Q

    nl_cat "./F.64"     "VG03.ALL"  ## MAK_LOGIC_DEV
    nl_cat "./F.66"     "VG03.ALL"  ## RET_QUEUE_HAN
    nl_cat "./F.70"     "VG03.ALL"  ## SWAP_CHAIN_WHATEVER

########################################

    nl_cat "./VG03.H"   "VG03.ALL"

########################################

##PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP##
##################################################
##//////////////////////////////////////////////##
##NOTE: LIB_ALL: Do not put extension!          ##
ext="temp_c11"   ## Temp_File_Extension         ##
c_v="c11"        ## Version of c to compile as  ##
d_n="Demo"       ## Demo Function Base Name     ##

demo_func=$LIB_ALL"_"$d_n ##EX: "GLEB_Demo"

##//////////////////////////////////////////////##
DEMO_CODE=$(cat << DEMO_CODE_HERE_DOC
//////////////////////////////////////////////////
    #include         "$LIB_ALL.ALL"       ////////   
    int main( void ){ $demo_func(); }     //////// 
//////////////////////////////////////////////////
DEMO_CODE_HERE_DOC
)

touch $LIB_ALL.$ext
>     $LIB_ALL.$ext
echo "$DEMO_CODE" >> $LIB_ALL.$ext

##################################################
MY_COMMAND_STRING=$(cat << GCC_COMMAND_01
    gcc                                     
    -x c                                    
    -c $LIB_ALL.$ext          
    -o  OBJ_FIL.o  
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
     
C1=" gcc -o EXE.exe OBJ_FIL.o "    
C2=" ./EXE.exe                "    
C3=" rm OBJ_FIL.o             "    
C4=" rm EXE.exe               "  
C5=" rm $LIB_ALL.$ext         "
$C1 && echo "OK:"$C1 || "FAIL:$C1"
$C2 && echo "OK:"$C2 || "FAIL:$C2"
$C3 && echo "OK:"$C3 || "FAIL:$C3"
$C4 && echo "OK:"$C4 || "FAIL:$C4"
$C5 && echo "OK:"$C5 || "FAIL:$C5"
##################################################
read -p "[END_OF_BUILD_SCRIPT:PressAnyKey]:"
##################################################
############## SC[ xxxxxxxxxx-sh ] ###############
######## ALSO_SEE[ xxxxxxxxxx-cx ] ###############
##################################################