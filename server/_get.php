<?php
  require_once dirname(__FILE__).'/class/TemperatureLog.php';

  class Get {
    private $pdo;
    private $selectLast;

    function __construct($pdo) {
      $this->pdo = $pdo;
      $this->selectLast = 'SELECT * FROM temperature_log ORDER BY created_at DESC LIMIT 1';
    }

    public function getLast() {
      $query = $this->pdo->prepare($this->selectLast);
      try {
          $query->execute();
      } catch(PDOExecption $e) {
          http_response_code(500);
          exit($e->message);
      }
      $results = $query->fetchAll(PDO::FETCH_CLASS, "TemperatureLog");

      return isset($results[0]) ? $results[0] : null;
    }
  }

 ?>
