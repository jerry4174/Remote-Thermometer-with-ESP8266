<?php
/*************************** 
Jerry was here 20211110 V1.0
PHP and HTML application to get and show temperature data from remote web servers (4 rooms).
Each thermometer has a port number forwarded in router to defined IP address.
HTML part is a simple table.
This program has anonym URL's.

****************************/


/*
	echo "\r\n";echo "<br/>";
	echo "Room 1:";
	echo "<br/>";
*/

        // create curl resource
        $ch50 = curl_init();

        // set url 50000, xxx change to your public IP address
        curl_setopt($ch50, CURLOPT_URL, "http://xxx.xxx.xxx.xxx:50000/");

        //return the transfer as a string
        curl_setopt($ch50, CURLOPT_RETURNTRANSFER, 1);

        // $output contains the output string
        $output50 = curl_exec($ch50);
/*
	echo "<br/>";
	echo $output50;
	echo "<br/>";
*/        
	// close curl resource to free up system resources
        curl_close($ch50); 
/*
	echo "<br/>";
	echo "Studio:";
	echo "<br/>";
*/
        // create curl resource
        $ch52 = curl_init();

        // set url 52000
        curl_setopt($ch52, CURLOPT_URL, "http://xxx.xxx.xxx.xxx:52000/");

        //return the transfer as a string
        curl_setopt($ch52, CURLOPT_RETURNTRANSFER, 1);

        // $output contains the output string
        $output52 = curl_exec($ch52);
/*	echo "<br/>";
	echo $output52;
	echo "<br/>";
*/
        // close curl resource to free up system resources
        curl_close($ch52);
       
	// create curl resource
        $ch53 = curl_init();

        // set url 53000
        curl_setopt($ch53, CURLOPT_URL, "http://xxx.xxx.xxx.xxx:53000/");

        //return the transfer as a string
        curl_setopt($ch53, CURLOPT_RETURNTRANSFER, 1);

        // $output contains the output string
        $output53 = curl_exec($ch53);
/*	echo "<br/>";
	echo $output53;
	echo "<br/>";
*/
        // close curl resource to free up system resources
        curl_close($ch53);

// create curl resource
        $ch51 = curl_init();

        // set url 51000
        curl_setopt($ch51, CURLOPT_URL, "http://xxx.xxx.xxx.xxx:51000/");

        //return the transfer as a string
        curl_setopt($ch51, CURLOPT_RETURNTRANSFER, 1);

        // $output contains the output string
        $output51 = curl_exec($ch51);
/*	echo "<br/>";
	echo $output51;
	echo "<br/>";
*/
        // close curl resource to free up system resources
        curl_close($ch51);

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<header>
<title>Temperature in Summer House</title>
</header>

<body>

<h2 align="center">Temparature in my rooms</h2>

<table width="600" align="center" cellspacing="0" cellpadding="5" border="1" >
  <tr>
    <th>Room</th>
    <th>Temparature</th>
    <th>Location</th>
  </tr>
  <tr>
    <td>1</td>
    <td align="center"><? echo $output52;?></td>
    <td align="center"><a href="./pics/sever_large.png" title="click here to see the full sized image"><img src="./pics/sever.png" alt="severní pokoj" width="100" height="130"></a></td>
   </tr>
  <tr>
    <td>2</td>
    <td align="center"><? echo $output50;?></td>
    <td align="center"><a href="./pics/studio_large.jpg" title="click here to see the full sized image"><img src="./pics/studio.jpg" alt="studio" ></a></td>
  </tr>
  <tr>
    <td>3</td>
  <td align="center"><? echo $output53;?></td>
    <td align="center"><a href="./pics/obyvak_large.jpg" title="click here to see the full sized image"><img src="./pics/obyvak.jpg" alt="studio"></a></td>
  </tr>
  <tr>
    <td>4</td>
   <td align="center"><? echo $output51;?></td>
    <td align="center"><a href="./pics/boiler_large.jpg" title="click here to see the full sized image"><img src="./pics/boiler.jpg"></a></td>
  </tr>
</table>
<p align="center">&nbsp;</p>
</body>
</html>