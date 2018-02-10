<?php
  require_once dirname(__FILE__).'/class/TemperatureLog.php';

  class Post {
    private $pdo;
    private $insert;
    private $select;

    function __construct($pdo) {
      $this->pdo = $pdo;
      $this->insert = 'INSERT INTO temperature_log (`temp_fahrenheit`, `temp_celsius`, `humidity_percent`)
        VALUES (:fahrenheit, :celsius, :humidity)';
      $this->select = 'SELECT * FROM temperature_log WHERE id = ?';
    }

    private function isValidJSON($str) {
      if (strlen($str) == 0) return false;
      json_decode($str);
      return json_last_error() == JSON_ERROR_NONE;
    }

    private function validateJson($json) {
      $required = array('fahrenheit', 'celsius', 'humidity');
      foreach ($required as $requiredParam) {
        if (!isset($json[$requiredParam])) {
          http_response_code(400);
          exit('Missing required field: '. $requiredParam);
        }
      }
    }

    public function create($rawInput) {
      $_JSON = $rawInput;
      if ($this->isValidJSON($_JSON)) {
        $_JSON = json_decode($_JSON, true);
      } else {
        http_response_code(400);
        exit('Invalid JSON');
      }

      $this->validateJson($_JSON);
      $params = array(
        ':fahrenheit' => $_JSON['fahrenheit'],
        ':celsius' => $_JSON['celsius'],
        ':humidity' => $_JSON['humidity']
      );

      $prepared = $this->pdo->prepare($this->insert);
      $insertedId = 0;
      try {
          $this->pdo->beginTransaction();
          $prepared->execute($params);
          $insertedId = $this->pdo->lastInsertId();
          $this->pdo->commit();
      } catch(PDOExecption $e) {
          $this->pdo->rollback();
          http_response_code(400);
          exit($e);
      }

      if ($insertedId == 0) {
        http_response_code(500);
        exit(json_encode(array('message' => 'An unexpected error occurred')));
      }

      $query = $this->pdo->prepare($this->select);

      try {
          $query->execute(array($insertedId));
      } catch(PDOExecption $e) {
          http_response_code(500);
          exit($e);
      }
      $results = $query->fetchAll(PDO::FETCH_CLASS, "TemperatureLog");

      return isset($results[0]) ? $results[0] : null;
    }
  }

 ?>
