drop database if exists `teamtwo`;

create database if not exists `teamtwo`;

use `teamtwo`;

create table if not exists `measurements` (
    id INT primary key auto_increment not null,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    temperature FLOAT(10, 2) unsigned zerofill,
    humidity FLOAT(10, 2) unsigned zerofill,
    heat_index FLOAT(10, 2) unsigned zerofill,
    co2_ppm INT
);