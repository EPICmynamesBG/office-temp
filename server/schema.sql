CREATE DATABASE OfficeTemp;

USE OfficeTemp;

CREATE TABLE IF NOT EXISTS temperature_log (
  id                INT UNSIGNED    NOT NULL  AUTO_INCREMENT,
  temp_fahrenheit   DECIMAL(5, 2)   NOT NULL,
  temp_celsius      DECIMAL(5, 2)   NOT NULL,
  humidity_percent  DECIMAL(5, 2)   NOT NULL,
  created_at        DATETIME        NOT NULL DEFAULT current_timestamp,
  PRIMARY KEY (id)
);
