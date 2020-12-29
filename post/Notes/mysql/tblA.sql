CREATE TABLE tblA(
#id int primary key not null autp_increment,
age int,
birth timestamp not null
);

insert into tblA(age,birth) values(22,now());
insert into tblA(age,birth) values(23,now());
insert into tblA(age,birth) values(24,now());

CREATE INDEX idx_A_ageBirth on tblA(age,birth);

select * from tblA;
