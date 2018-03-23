<?php

  class TemperatureLog implements JsonSerializable {
    public $id;
    public $temp_fahrenheit;
    public $temp_celsius;
    public $humidty_percent;
    public $created_at;

    public function __construct($arr = array()) {
      if (sizeof($arr) == 0) { // PDO populated
        $this->temp_fahrenheit = TemperatureLog::parseFloat($this->temp_fahrenheit);
        $this->temp_celsius = TemperatureLog::parseFloat($this->temp_celsius);
        $this->humidity_percent = TemperatureLog::parseFloat($this->humidity_percent);
        $this->created_at = DateTime::createFromFormat('Y-m-d H:i:s', $this->created_at, new DateTimeZone('America/New_York'));
        return;
      }
      $this->id = $arr['id'];
      $this->temp_fahrenheit = TemperatureLog::parseFloat($arr['temp_fahrenheit']);
      $this->temp_celsius = TemperatureLog::parseFloat($arr['temp_celsius']);
      $this->humidity_percent = TemperatureLog::parseFloat($arr['humidity_percent']);
      $this->created_at = DateTime::createFromFormat('Y-m-d H:i:s', $arr['created_at'], new DateTimeZone('America/New_York'));
    }

    private static function parseFloat($val) {
      return number_format(floatval($val), 2);
    }

    public function jsonSerialize() {
      return array(
        'id' => $this->id,
        'fahrenheit' => $this->temp_fahrenheit,
        'celsius' => $this->temp_celsius,
        'humidity' => $this->humidity_percent,
        'time' => $this->created_at->format('Y-m-d H:i:s T')
      );
    }

    private function createdToday() {
      $createdAt = clone $this->created_at;
      $createdAt->setTime(0, 0, 0);

      $now = new DateTime();
      $now->setTime(0, 0, 0);

      $diff = $now->diff($createdAt);
      $diffDays = (integer)$diff->format( "%R%a" );
      return $diffDays == 0;
    }

    public function __toString() {
      $time = $this->createdToday() ?
        $this->created_at->format('h:ia') :
        $this->created_at->format('h:ia D, F jS');
      return 'Temperature: ' . $this->temp_fahrenheit . "°F\n".
        'Humidity: '.$this->humidity_percent ."%\n".
        'As of ' . $time;
    }

    public function toSlack() {
      $time = $this->createdToday() ?
        $this->created_at->format('h:ia') :
        $this->created_at->format('h:ia D, F jS');

      $text = '```'.
        'Temperature: ' . $this->temp_fahrenheit . "°F\n".
        'Humidity: '.$this->humidity_percent ."%\n".
        'As of ' . $time.
        '```';
      return array(
        'text' => $text
      );
    }
  }

 ?>
