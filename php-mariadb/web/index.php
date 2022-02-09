<?php

$json_response = NULL;

$conn = new mysqli("db", "web", "password", "web");
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
     // The request is using the POST method
    $json = file_get_contents('php://input');
    $answer = json_decode($json, true);
    $sql = $conn->prepare('INSERT INTO answers (question_id, answer) VALUES (?, ?)');
    $sql->bind_param('is', intval($answer['question_id']), strval($answer['answer']));
    $sql->execute();
    $answer['id'] = intval($sql->insert_id);
    $json_reponse = json_encode($answer);
    header('HTTP/1.1 200 OK');
    header('Content-Type: application/json; charset=utf-8');
    echo $json_reponse;
}
else {
    $sql = "SELECT id, question_id, answer FROM answers";
    $result = $conn->query($sql);
    $answers = array();
    while ($row = mysqli_fetch_assoc($result))
    {
        $answers[] = $row;
    }
    $json_response = json_encode($answers);

    header('HTTP/1.1 200 OK');
    header('Content-Type: application/json; charset=utf-8');
    echo $json_response;

}
$conn->close();

?>
