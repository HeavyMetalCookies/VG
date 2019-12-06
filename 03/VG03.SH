##################################################
############## SC[ xxxxxxxxxx-sh ] ###############
######## ALSO_SEE[ xxxxxxxxxx-cx ] ###############
##################################################




                LIB_ALL="VG03" 




##################################################
##PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP##
                                                    
            ######################### 
            ##  PRJ Specific Code  ##
            #########################

touch "VG03.ALL"  ##Create
    > "VG03.ALL"  ##Clean

cat "./W32/DLLL/DLLL.COMSET"  >> "VG03.ALL"
cat "./W32/DLLL/TARG/W10.X64" >> "VG03.ALL"
cat "./W32/DLLL/DLLL.H"       >> "VG03.ALL" 

##GATHER_FUNCTION_POINTERS:
cat "./01/F01._"               >> "VG03.ALL"

cat "./VG03.H"                >> "VG03.ALL"



##PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP##
##################################################
##//////////////////////////////////////////////##
##NOTE: LIB_ALL: Do not put extension!          ##
ext="temp_c11"   ## Temp_File_Extension         ##
c_v="c11"        ##  version of c to compile as ##
##//////////////////////////////////////////////##
DEMO_CODE=$(cat << DEMO_CODE_HERE_DOC
//////////////////////////////////////////////////
    #include         "$LIB_ALL.ALL"       ////////   
    int main( void ){ $LIB_ALL.Demo(); }  //////// 
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