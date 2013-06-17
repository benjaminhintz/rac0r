<?php
$list = array();

$dir = "tracks";
$dirHandle = opendir($dir);
while($fileHandle = readdir($dirHandle)) {
	if($fileHandle != "." && $fileHandle != ".." && preg_match('(.track)', $fileHandle)) {
		$list[] = $fileHandle;
	}
}

sort($list);

foreach($list AS $track) {
	echo $track . "\n";
}
?>