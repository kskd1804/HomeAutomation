<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Untitled Document</title>
</head>

<body>
<form method="post" action="getInput.php">
<p>
<label for="Host">Host:</label>
<input type="text" name="hostname"/>
</p>
<p>
<label for="Username">Username:</label>
<input type="text" name="username"/>
</p>
<p>
<label for="Password">Password:</label>
<input type="password" name="password"/>
</p>
<p>
<label for="Database">Database:</label>
<input type="text" name="database"/>
</p>
<p>
<label for="RelayID">Relay ID:</label>
<input type="text" name="relay_id"/>
</p>
<p>
<label for="LastID">Last ID:</label>
<input type="text" name="last_id"/>
</p>
<input type="submit" name="submit" value="Get Records!"/>
</form>
</body>
</html>
