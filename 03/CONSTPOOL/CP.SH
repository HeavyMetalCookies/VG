##################################################//////////////
################## SC[ HKMF_C11_DEMO_64 ] ########//////////////
##################################################//////////////



include_this_file="CP._"
run_this_function="CONSTPOOL_Main"



##################################################//////////////
##################################################//////////////
##################################################//////////////
DEMO_C11_CODE=$(cat << DEMO_C11_CODE_HERE_DOC
//////////////////////////////////////////////////
    #include "$include_this_file"           //[]//
                                                //
    int                                         //
    main(                                       //
        void                                    //
    ){                                          //
                                                //
        $run_this_function();                   //
                                                //
    }                                           //
//////////////////////////////////////////////////
DEMO_C11_CODE_HERE_DOC
)

touch $base_name_no_ext.C11                    ###
>     $base_name_no_ext.C11                    ###
echo "$DEMO_C11_CODE" >> $base_name_no_ext.C11 ###

##################################################
MY_COMMAND_STRING=$(cat << GCC_COMMAND_01
    gcc                                     
    -x c                                    
    -c $base_name_no_ext.C11          
    -o my_object_file.o                     
    -m64                                    
GCC_COMMAND_01
)                                       
C=$MY_COMMAND_STRING  ############################//////////////
C=$C"-Werror        " ## WarningsAreErrors      ##//////////////
C=$C"-Wfatal-errors " ## StopAtFirstError       ##//////////////
C=$C"-Wpedantic     " ## UseStrictISO_C         ##//////////////
C=$C"-Wall          " ## WarnAboutAnyWeirdCode  ##//////////////
C=$C"-Wextra        " ## "-Wall" WarningsExtra  ##//////////////
C=$C"-std=c11       " ## VersionOf_C_ToUse      ##//////////////
MY_COMMAND_STRING=$C  ############################//////////////

echo $MY_COMMAND_STRING
     $MY_COMMAND_STRING
     
C1=" gcc -o EXE.exe my_object_file.o "    
C2=" ./EXE.exe                       "    
C3=" rm my_object_file.o             "    
C4=" rm EXE.exe                      "  
C5=" rm $base_name_no_ext.C11        "
$C1 && echo "OK:"$C1 || "FAIL:$C1"
$C2 && echo "OK:"$C2 || "FAIL:$C2"
$C3 && echo "OK:"$C3 || "FAIL:$C3"
$C4 && echo "OK:"$C4 || "FAIL:$C4"
$C5 && echo "OK:"$C5 || "FAIL:$C5"
##################################################//////////////
read -p "[END_OF_BUILD_SCRIPT:PressAnyKey]:"    ##//////////////
##################################################//////////////
################## SC[ HKMF_C11_DEMO_64 ] ########//////////////
##################################################//////////////