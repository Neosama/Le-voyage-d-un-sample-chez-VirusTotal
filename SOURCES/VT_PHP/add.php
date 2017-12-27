<?php

//Fichier enregistrement PHP

function Hex2String($hex){
    $string='';
    for ($i=0; $i < strlen($hex)-1; $i+=2){
        $string .= chr(hexdec($hex[$i].$hex[$i+1]));
    }
    return $string;
}

$filename_log = "benzai_logs";

if (file_exists($filename_log))
{

    if(empty($_GET['zz']) && empty($_GET['ee']))
    {
       echo '<p>Empty ZZ & EE!</p>';
    }

    else
    {
        if($fichier=fopen($filename_log,"a+"))
        {
		  fputs($fichier,"|");
		  fputs($fichier,time());
		  fputs($fichier,"|");
		  fputs($fichier,$_SERVER['REMOTE_ADDR']); // WRITE IP
		  fputs($fichier,"|");
          fputs($fichier,Hex2String($_GET['zz'])); // WRITE UID
          fputs($fichier,"|");
          fputs($fichier,Hex2String($_GET['ee'])); // WRITE DATA
		  fputs($fichier,"\n");
		  fclose($fichier);
        }
		
		// LOG PERSISTANT
		//if($fichier=fopen($filename_all_log,"a+"))
        //{
		//  fputs($fichier,"|");
		//  fputs($fichier,time());
		//  fputs($fichier,"|");
		//  fputs($fichier,$_SERVER['REMOTE_ADDR']); // WRITE IP
		//  fputs($fichier,"|");
        //  fputs($fichier,Hex2String($_GET['zz'])); // WRITE UID
        //  fputs($fichier,"|");
        //  fputs($fichier,Hex2String($_GET['ee'])); // WRITE DATA
		//  fputs($fichier,"\n");
		//  fclose($fichier);
        //}
    }
}
else
{
    echo '<p>Not File logs!</p>';
}

?>