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


##NO Dependencies besides standard library includes:
################################################################

##  nl_cat "./MEM_MAN/CONSTPOOL/CP._"       "VG03.ALL"
    nl_cat         "./CONSTPOOL/CP._"       "VG03.ALL"

################################################################

nl_cat "./W32/DLLL/DLLL.COMSET"     "VG03.ALL"
nl_cat "./W32/DLLL/TARG/W10.X64"    "VG03.ALL"
nl_cat "./W32/DLLL/DLLL.H"          "VG03.ALL" 

################################################################

##  nl_cat "./MEM_MAN/HOMOPOOL/HP._"        "VG03.ALL"
    nl_cat         "./HOMOPOOL/HP._"        "VG03.ALL"

################################################################


## CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC ##
## Once again, couldn't back up from "E.01"                   ##
## Decided to back up to C instead of D since Intent          ##
## was to add a static configuration file.                    ##
## Started with "C50" / "C.50" this time instead of           ##
## making mistakeof starting with "C01" / "C.01" .            ##                      ##
## CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC ##

    nl_cat "./C.50" "VG03.ALL"

## CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC ##

## I can't back up any futher, so moving down to "E"
## EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE ##

    nl_cat "./E.01" "VG03.ALL"

## EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE ##

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

    nl_cat "./F.61.05"  "VG03.ALL"  ## DEVICEEXTLIST

    ## The graphics + compute queue selections
    ## are in PHYDEV_SELECT. That is worthy
    ## of refactor by splitting "F.62" into two files.
    nl_cat "./F.62"     "VG03.ALL"  ## PHYDEV_SELECT
    nl_cat "./F.63"     "VG03.ALL"  ## GET_PRESENT_Q

    nl_cat "./F.64"     "VG03.ALL"  ## MAK_LOGIC_DEV
    nl_cat "./F.66"     "VG03.ALL"  ## RET_QUEUE_HAN
    nl_cat "./F.70"     "VG03.ALL"  ## SWAP_CHAIN_WHATEVER
    nl_cat "./F.80"     "VG03.ALL"  ## GET_SWAP_CHAIN_IMAGES
    nl_cat "./F.90"     "VG03.ALL"  ## SWAPCHAIN_VEW
    nl_cat "./F.100"    "VG03.ALL"  ## VERT+FRAG Source
    nl_cat "./F.110"    "VG03.ALL"  ## Make Path To FinderFile
    nl_cat "./F.120"    "VG03.ALL"  ## Does FinderFile Exist?
    nl_cat "./F.130"    "VG03.ALL"  ## FIND:glslangvalidator.exe

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