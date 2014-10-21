<?php
function rndname(){
	$string = "";
	$max = 20;
	$chars = "abcdefghijklmnopqrstuvwxwz0123456789";
	for($i = 0; $i < $max; $i++){
		$rand_key = mt_rand(0, strlen($chars));
		$string  .= substr($chars, $rand_key, 1);
	}
	return str_shuffle($string);
}
$out = '';
if (!isset($_COOKIE['user_details'])) {
	$out = "a new user!";
	$filename = "user_".rndname().".dat";
	$f = fopen('/tmp/level1/' . $filename, 'w+');

	$str = $_SERVER['REMOTE_ADDR']." using ".$_SERVER['HTTP_USER_AGENT'];
	fwrite($f, $str);
	fclose($f);
	setcookie('user_details', $filename);
}
else {
	$out = file_get_contents('/tmp/level1/'.$_COOKIE['user_details']);
}	
?>

<html>
<head>
<title>Geekcamp.sg CTF</title>
</head>

<body>
<div>

<h1> Hello, and welcome to GeekcampSG's CTF!  </h1>

<h2> What do I do?  </h2>
<ul>
<li> Capture the flags. Your goal is to get to the server, and capture each flag. </li>
<li> Flags are stored in the home directory of your target user. </li>
<li> Your first target is the flag of user level1@ctf.geekcamp.sg. </li>
<li> When you capture a flag, send a <b>plaintext</b> email to <a href="mailto:ctf@rahul.ag">ctf@rahul.ag</a>. </li>
<li> Once you have the final flag, find <b><a href="http://geekcamp.sg/pages/team">Rahul</a></b> and give him the flag code <b>on a piece of paper</b>, <b>in person</b>. </li>
<li> You <b>will</b> be required to show your method of attack for each flag. </li>
<li> The first person to capture the last flag, or the person with the most flags &amp; the best solution at 1800 hrs wins. </li>
</ul>

<h2> Rules </h2>

<ul>
<li> Keep it legit, don't attack any of the infrastructure at the venue. </li>
<li> Do not do anything that <b>prevents</b> other participants from capturing a flag. </li>
<li> Do not attempt to undermine the continued operation of any of the following: web server, vpn server, and any screen or tmux sessions. </li>
<li> The judges' decision is final, and you may be disqualified for any violation of the above. </li>
</ul>

<small> This is level1, and you are <?php echo $out ?> </small>

</body>
</html>
