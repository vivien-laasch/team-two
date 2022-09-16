drop database if exists `team-two`;

create database if not exists `team-two`;

use `team-two`;

create table if not exists `measurements` (
    id INT primary key auto_increment not null,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    humidity FLOAT(10,2) unsigned zerofill,
	temperature FLOAT(10,2) unsigned zerofill);
    
   
select  from measurements;
   