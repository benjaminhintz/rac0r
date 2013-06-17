<?php
$dir = "tracks";

if(key_exists("track", $_GET)) {
	$file = $_GET['track'];
	if(file_exists($dir . '/' . $file)) {
		echo file_get_contents($dir . '/' . $file);
	} else {
		echo false;
	}
} else {
	// liste
	$dirHandle = opendir($dir);
	$output = array();
	$files = array();

	while($fileHandle  = readdir($dirHandle)) {
		if($fileHandle != '.' && $fileHandle != '..') {
			$files[] = $fileHandle;
		}
	}

	sort($files);

	foreach($files AS $fileHandle) {
		$parts = explode('.', $fileHandle);
		if($parts[1] == 'track') {
			$output[] = array('track' => $fileHandle, 'image' => $dir . '/' . $parts[0] . '.png');
		}
	}
	echo json_encode($output);
}

?>