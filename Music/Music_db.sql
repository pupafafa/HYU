-- --------------------------------------------------------
-- 호스트:                          127.0.0.1
-- 서버 버전:                        10.5.6-MariaDB - mariadb.org binary distribution
-- 서버 OS:                        Win64
-- HeidiSQL 버전:                  11.0.0.5919
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- music 데이터베이스 구조 내보내기
CREATE DATABASE IF NOT EXISTS `music` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `music`;

-- 테이블 music.admin 구조 내보내기
CREATE TABLE IF NOT EXISTS `admin` (
  `admin_id` int(11) NOT NULL DEFAULT 0,
  `admin_password` varchar(20) NOT NULL DEFAULT '0000',
  `admin_name` varchar(30) DEFAULT NULL,
  `admin_phone_number` varchar(15) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 music.admin:~0 rows (대략적) 내보내기
/*!40000 ALTER TABLE `admin` DISABLE KEYS */;
INSERT INTO `admin` (`admin_id`, `admin_password`, `admin_name`, `admin_phone_number`) VALUES
	(90000, '1234', 'admin1', '010-9189-0713');
/*!40000 ALTER TABLE `admin` ENABLE KEYS */;

-- 테이블 music.album 구조 내보내기
CREATE TABLE IF NOT EXISTS `album` (
  `Album_ID` int(11) NOT NULL DEFAULT 0,
  `Title_ID` int(11) NOT NULL DEFAULT 0,
  `album_name` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`Album_ID`),
  KEY `Title_ID` (`Title_ID`),
  CONSTRAINT `album_ibfk_1` FOREIGN KEY (`Title_ID`) REFERENCES `song` (`Song_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 music.album:~23 rows (대략적) 내보내기
/*!40000 ALTER TABLE `album` DISABLE KEYS */;
INSERT INTO `album` (`Album_ID`, `Title_ID`, `album_name`) VALUES
	(10000, 20000, 'Be'),
	(10001, 20005, '21'),
	(10002, 20009, '25'),
	(10003, 20013, 'How I\'m Feeling'),
	(10004, 20018, 'I\'m So Tired'),
	(10005, 20019, 'bellyache'),
	(10006, 20020, 'Don\'t Smaile at Me'),
	(10007, 20026, 'Songs about Jane'),
	(10008, 20034, 'V'),
	(10009, 20040, 'Torches'),
	(10010, 20047, 'Scared hearts club'),
	(10011, 20052, 'Honestly'),
	(10012, 20057, 'We\'ve Done Something Wonderful'),
	(10013, 20064, 'Sleepless in______'),
	(10014, 20068, 'Sleeping beauty'),
	(10015, 20069, 'THE STORY BEGINS'),
	(10016, 20075, 'TWICEcoaster PART2'),
	(10017, 20081, 'SQUARE UP'),
	(10018, 20086, 'KILL THIS LOVE'),
	(10019, 20091, 'We'),
	(10020, 20095, 'Database'),
	(10021, 20098, 'System'),
	(19999, 29999, 'Unknown');
/*!40000 ALTER TABLE `album` ENABLE KEYS */;

-- 테이블 music.album_song 구조 내보내기
CREATE TABLE IF NOT EXISTS `album_song` (
  `album` int(11) NOT NULL DEFAULT 0,
  `song` int(11) NOT NULL DEFAULT 0,
  `track_num` int(11) DEFAULT NULL,
  PRIMARY KEY (`album`,`song`),
  KEY `song` (`song`),
  CONSTRAINT `album_song_ibfk_1` FOREIGN KEY (`album`) REFERENCES `album` (`Album_ID`),
  CONSTRAINT `album_song_ibfk_2` FOREIGN KEY (`song`) REFERENCES `song` (`Song_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 music.album_song:~103 rows (대략적) 내보내기
/*!40000 ALTER TABLE `album_song` DISABLE KEYS */;
INSERT INTO `album_song` (`album`, `song`, `track_num`) VALUES
	(10000, 20000, 1),
	(10000, 20001, 2),
	(10000, 20002, 3),
	(10000, 20003, 4),
	(10000, 20004, 5),
	(10001, 20005, 1),
	(10001, 20006, 2),
	(10001, 20007, 3),
	(10001, 20008, 4),
	(10002, 20005, 2),
	(10002, 20009, 1),
	(10002, 20010, 3),
	(10002, 20011, 4),
	(10002, 20012, 5),
	(10003, 20013, 1),
	(10003, 20014, 2),
	(10003, 20015, 3),
	(10003, 20016, 4),
	(10003, 20017, 5),
	(10004, 20018, 1),
	(10005, 20019, 1),
	(10006, 20019, 2),
	(10006, 20020, 1),
	(10006, 20021, 3),
	(10006, 20022, 4),
	(10006, 20023, 5),
	(10006, 20024, 6),
	(10006, 20025, 7),
	(10007, 20026, 1),
	(10007, 20027, 2),
	(10007, 20028, 3),
	(10007, 20029, 4),
	(10007, 20030, 5),
	(10007, 20031, 6),
	(10007, 20032, 7),
	(10007, 20033, 8),
	(10008, 20034, 1),
	(10008, 20035, 2),
	(10008, 20036, 3),
	(10008, 20037, 4),
	(10008, 20038, 5),
	(10008, 20039, 6),
	(10009, 20040, 1),
	(10009, 20041, 2),
	(10009, 20042, 3),
	(10009, 20043, 4),
	(10009, 20044, 5),
	(10009, 20045, 6),
	(10009, 20046, 7),
	(10010, 20047, 1),
	(10010, 20048, 2),
	(10010, 20049, 3),
	(10010, 20050, 4),
	(10010, 20051, 5),
	(10011, 20052, 1),
	(10011, 20053, 2),
	(10011, 20054, 3),
	(10011, 20055, 4),
	(10011, 20056, 5),
	(10012, 20057, 1),
	(10012, 20058, 2),
	(10012, 20059, 3),
	(10012, 20060, 4),
	(10012, 20061, 5),
	(10012, 20062, 6),
	(10012, 20063, 7),
	(10013, 20064, 1),
	(10013, 20065, 2),
	(10013, 20066, 3),
	(10013, 20067, 4),
	(10014, 20068, 1),
	(10015, 20069, 1),
	(10015, 20070, 1),
	(10015, 20071, 2),
	(10015, 20072, 3),
	(10015, 20073, 4),
	(10015, 20074, 5),
	(10016, 20075, 1),
	(10016, 20076, 2),
	(10016, 20077, 3),
	(10016, 20078, 4),
	(10016, 20079, 5),
	(10016, 20080, 6),
	(10017, 20081, 1),
	(10017, 20082, 2),
	(10017, 20083, 3),
	(10017, 20084, 4),
	(10017, 20085, 5),
	(10018, 20086, 1),
	(10018, 20087, 2),
	(10018, 20088, 3),
	(10018, 20089, 4),
	(10018, 20090, 5),
	(10019, 20091, 1),
	(10019, 20092, 2),
	(10019, 20093, 3),
	(10019, 20094, 4),
	(10020, 20095, 1),
	(10020, 20096, 2),
	(10020, 20097, 3),
	(10021, 20098, 1),
	(10021, 20099, 2),
	(19999, 29999, 1);
/*!40000 ALTER TABLE `album_song` ENABLE KEYS */;

-- 테이블 music.artist 구조 내보내기
CREATE TABLE IF NOT EXISTS `artist` (
  `Artist_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `Artist_name` varchar(45) NOT NULL DEFAULT '0',
  PRIMARY KEY (`Artist_id`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8;

-- 테이블 데이터 music.artist:~13 rows (대략적) 내보내기
/*!40000 ALTER TABLE `artist` DISABLE KEYS */;
INSERT INTO `artist` (`Artist_id`, `Artist_name`) VALUES
	(1, 'Adele'),
	(2, 'Lauv'),
	(3, 'Billie Eilish'),
	(4, 'Maroon5'),
	(5, 'Foster the People'),
	(6, 'EricNam'),
	(7, 'EPICK HIGH'),
	(8, 'TWICE'),
	(9, 'BLACKPINK'),
	(10, 'NanYeong'),
	(11, 'Villain'),
	(12, 'WonSeok'),
	(13, 'BTS'),
	(15, 'test_artist');
/*!40000 ALTER TABLE `artist` ENABLE KEYS */;

-- 테이블 music.artist_history 구조 내보내기
CREATE TABLE IF NOT EXISTS `artist_history` (
  `artist` int(11) unsigned NOT NULL DEFAULT 0,
  `content` varchar(60) NOT NULL,
  PRIMARY KEY (`artist`,`content`),
  CONSTRAINT `history_artist` FOREIGN KEY (`artist`) REFERENCES `artist` (`Artist_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 music.artist_history:~29 rows (대략적) 내보내기
/*!40000 ALTER TABLE `artist_history` DISABLE KEYS */;
INSERT INTO `artist_history` (`artist`, `content`) VALUES
	(1, '2013 Debut '),
	(1, 'Win 2016 Grammy \'Top Female Vocal\''),
	(1, 'Win 2020 Grammy \'Top Female Vocal\''),
	(2, '2016 Debut '),
	(2, 'Win 2020 Academy \'Top Actor\''),
	(3, '2018 Debut '),
	(3, 'Win 2019 \'Best New Singer\''),
	(3, 'Win 2019 \'World\'s Best Teen Vocal\''),
	(4, '2010 Debut '),
	(4, 'Win 2019 Band Academy \'Best Band\''),
	(5, '2009 Debut '),
	(5, 'Win 2015 \'My Highschool Best Band\''),
	(6, 'Debut 2015'),
	(7, '2002 Debut'),
	(7, '2018 Show Me the Money Judge'),
	(7, 'Korea HipHop Festival Panel'),
	(8, '2015 Debute'),
	(8, '2016 Melon Music Award \'Rookie of the Year\''),
	(8, 'My army Happy virus'),
	(9, 'Debut 2017'),
	(9, 'My army best sexy idol'),
	(10, '2019 Debut'),
	(10, '2020 Mnet Super Rookie'),
	(11, 'Debut 2020'),
	(11, 'Get A+ on Database System on 2020-2'),
	(12, 'Database System Villain'),
	(13, '2017 Debut '),
	(13, 'Win \'2020 Best Idol\''),
	(13, 'Win 2019 Music Festa \'Best GROUP Performance\'');
/*!40000 ALTER TABLE `artist_history` ENABLE KEYS */;

-- 테이블 music.composer 구조 내보내기
CREATE TABLE IF NOT EXISTS `composer` (
  `composer_ID` int(11) NOT NULL DEFAULT 0,
  `composer_name` varchar(40) NOT NULL,
  PRIMARY KEY (`composer_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 music.composer:~14 rows (대략적) 내보내기
/*!40000 ALTER TABLE `composer` DISABLE KEYS */;
INSERT INTO `composer` (`composer_ID`, `composer_name`) VALUES
	(30000, 'Idol Master'),
	(30001, 'Adele'),
	(30002, 'Lauv'),
	(30003, 'Billie Eilish'),
	(30004, 'Adam Levine'),
	(30005, 'Foster the People'),
	(30006, 'EricNam'),
	(30007, 'Drunken Tiger'),
	(30008, 'Tablo'),
	(30009, 'Missra Jinn'),
	(30010, 'SEKAINO OWARI'),
	(30011, 'YeongWon'),
	(30012, 'Villain'),
	(30013, 'WonSeok');
/*!40000 ALTER TABLE `composer` ENABLE KEYS */;

-- 테이블 music.composer_history 구조 내보내기
CREATE TABLE IF NOT EXISTS `composer_history` (
  `composer` int(11) NOT NULL DEFAULT 0,
  `content` varchar(40) NOT NULL,
  PRIMARY KEY (`composer`,`content`),
  CONSTRAINT `composer_history_ibfk_1` FOREIGN KEY (`composer`) REFERENCES `composer` (`composer_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 music.composer_history:~0 rows (대략적) 내보내기
/*!40000 ALTER TABLE `composer_history` DISABLE KEYS */;
/*!40000 ALTER TABLE `composer_history` ENABLE KEYS */;

-- 테이블 music.list_song 구조 내보내기
CREATE TABLE IF NOT EXISTS `list_song` (
  `list` int(11) NOT NULL DEFAULT 0,
  `song` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`song`,`list`),
  KEY `list` (`list`),
  CONSTRAINT `list_song_ibfk_1` FOREIGN KEY (`list`) REFERENCES `playlist` (`list_id`),
  CONSTRAINT `list_song_ibfk_2` FOREIGN KEY (`song`) REFERENCES `song` (`Song_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 music.list_song:~0 rows (대략적) 내보내기
/*!40000 ALTER TABLE `list_song` DISABLE KEYS */;
INSERT INTO `list_song` (`list`, `song`) VALUES
	(40017, 20001),
	(40016, 20005),
	(40019, 20005),
	(40019, 20006),
	(40019, 20007),
	(40019, 20008),
	(40019, 20009),
	(40019, 20010),
	(40019, 20011),
	(40019, 20012),
	(40017, 20013),
	(40016, 20019),
	(40017, 20022),
	(40016, 20026),
	(40018, 20031),
	(40018, 20032),
	(40017, 20033),
	(40018, 20033),
	(40018, 20034),
	(40018, 20036),
	(40018, 20037),
	(40018, 20039),
	(40018, 20040),
	(40017, 20083),
	(40017, 20098);
/*!40000 ALTER TABLE `list_song` ENABLE KEYS */;

-- 테이블 music.playlist 구조 내보내기
CREATE TABLE IF NOT EXISTS `playlist` (
  `list_id` int(11) NOT NULL AUTO_INCREMENT,
  `list_name` varchar(20) NOT NULL,
  `list_owner` int(11) NOT NULL DEFAULT 0,
  `create_date` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`list_id`)
) ENGINE=InnoDB AUTO_INCREMENT=40020 DEFAULT CHARSET=utf8;

-- 테이블 데이터 music.playlist:~0 rows (대략적) 내보내기
/*!40000 ALTER TABLE `playlist` DISABLE KEYS */;
INSERT INTO `playlist` (`list_id`, `list_name`, `list_owner`, `create_date`) VALUES
	(40016, 'myplaylist', 50006, '2020/12/07 19:23:37'),
	(40017, 'JANE LIST', 50008, '2020-12-11'),
	(40018, 'New list', 50006, '2020-12-11'),
	(40019, 'ADELE List', 50006, '2020-12-25');
/*!40000 ALTER TABLE `playlist` ENABLE KEYS */;

-- 테이블 music.song 구조 내보내기
CREATE TABLE IF NOT EXISTS `song` (
  `Song_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Song_name` varchar(45) DEFAULT NULL,
  `Play_time` varchar(50) DEFAULT NULL,
  `Composer` int(11) DEFAULT NULL,
  `Artist` int(11) unsigned NOT NULL,
  `Registration_date` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`Song_ID`),
  KEY `song_artist` (`Artist`),
  CONSTRAINT `song_artist` FOREIGN KEY (`Artist`) REFERENCES `artist` (`Artist_id`)
) ENGINE=InnoDB AUTO_INCREMENT=30005 DEFAULT CHARSET=utf8;

-- 테이블 데이터 music.song:~101 rows (대략적) 내보내기
/*!40000 ALTER TABLE `song` DISABLE KEYS */;
INSERT INTO `song` (`Song_ID`, `Song_name`, `Play_time`, `Composer`, `Artist`, `Registration_date`) VALUES
	(20000, 'Life goes on', '00:03:28', 30000, 13, '2020-03-20'),
	(20001, 'Fly to My Room', '00:03:43', 30000, 13, '2020-03-20'),
	(20002, 'Blue & Grey', '00:04:15', 30000, 13, '2020-03-20'),
	(20003, 'Telepathy', '00:03:23', 30000, 13, '2020-03-20'),
	(20004, 'Disease', '00:04:00', 30000, 13, '2020-03-20'),
	(20005, 'Someone like you', '00:04:46', 30001, 1, '2011-09-19'),
	(20006, 'Lovesong', '00:05:17', 30001, 1, '2011-09-19'),
	(20007, 'Turning Tables', '00:04:11', 30001, 1, '2011-09-19'),
	(20008, 'Don\'t you remember', '00:04:04', 30001, 1, '2011-09-19'),
	(20009, 'Hello', '00:04:56', 30001, 1, '2015-04-20'),
	(20010, 'Send My Love', '00:03:44', 30001, 1, '2015-04-20'),
	(20011, 'Remedy', '00:04:06', 30001, 1, '2015-04-20'),
	(20012, 'All I Ask', '00:04:32', 30001, 1, '2015-04-20'),
	(20013, 'How I\'m feeling', '00:03:17', 30002, 2, '2020-01-06'),
	(20014, 'Believed', '00:02:50', 30002, 2, '2020-01-06'),
	(20015, 'Billy', '00:03:01', 30002, 2, '2020-01-06'),
	(20016, 'Changes', '00:02:41', 30002, 2, '2020-01-06'),
	(20017, 'Julia', '00:03:28', 30002, 2, '2020-01-06'),
	(20018, 'I\'m so tired', '00:02:42', 30002, 2, '2020-09-20'),
	(20019, 'Bellyache', '00:02:59', 30003, 3, '2017-07-13'),
	(20020, 'COPYCAT', '00:03:18', 30003, 3, '2017-08-15'),
	(20021, 'idontwannabeyouanymore', '00:03:24', 30003, 3, '2017-08-15'),
	(20022, 'My Boy', '00:02:51', 30003, 3, '2017-08-15'),
	(20023, 'Watch', '00:02:58', 30003, 3, '2017-08-15'),
	(20024, 'Pary Favor', '00:03:25', 30003, 3, '2017-08-15'),
	(20025, 'Ocean Eyes', '00:03:21', 30003, 3, '2017-08-15'),
	(20026, 'This Love', '00:03:27', 30004, 4, '2002-11-25'),
	(20027, 'Shiver', '00:03:00', 30004, 4, '2002-11-25'),
	(20028, 'She will be loved', '00:04:18', 30004, 4, '2002-11-25'),
	(20029, 'Tangled', '00:03:19', 30004, 4, '2002-11-25'),
	(20030, 'The Sun', '00:03:19', 30004, 4, '2002-11-25'),
	(20031, 'Must get out', '00:04:00', 30004, 4, '2002-11-25'),
	(20032, 'Secret', '00:04:55', 30004, 4, '2002-11-25'),
	(20033, 'Through with you', '00:03:02', 30004, 4, '2002-11-25'),
	(20034, 'Maps', '00:03:10', 30004, 4, '2015-01-28'),
	(20035, 'Aniamals', '00:03:52', 30004, 4, '2015-01-28'),
	(20036, 'It was always you', '00:04:00', 30004, 4, '2015-01-28'),
	(20037, 'Unkiss me', '00:03:59', 30004, 4, '2015-01-28'),
	(20038, 'Leaving California', '00:03:24', 30004, 4, '2015-01-28'),
	(20039, 'Lost stars', '00:04:28', 30004, 4, '2015-01-28'),
	(20040, 'Pumped up kicks', '00:04:00', 30005, 5, '2011-05-10'),
	(20041, 'Helena beat', '00:04:37', 30005, 5, '2011-05-10'),
	(20042, 'Call it What you want', '00:03:59', 30005, 5, '2011-05-10'),
	(20043, 'Don\' stop', '00:02:55', 30005, 5, '2011-05-10'),
	(20044, 'Waste', '00:00:26', 30005, 5, '2011-05-10'),
	(20045, 'Houndini', '00:03:23', 30005, 5, '2011-05-10'),
	(20046, 'Miss you', '00:03:33', 30005, 5, '2011-05-10'),
	(20047, 'Pay the man', '00:03:53', 30005, 5, '2011-05-10'),
	(20048, 'Doing it for the Money', '00:03:46', 30005, 5, '2011-05-10'),
	(20049, 'Sit Next to Me', '00:04:03', 30005, 5, '2011-05-10'),
	(20050, 'SHC', '00:04:08', 30005, 5, '2011-05-10'),
	(20051, 'I Love My Friends', '00:03:45', 30005, 5, '2011-05-10'),
	(20052, 'Honestly', '00:03:26', 30006, 6, '2018-02-23'),
	(20053, 'Potion', '00:03:32', 30006, 6, '2018-02-23'),
	(20054, 'This is Not A Love Song', '00:03:30', 30007, 6, '2018-02-23'),
	(20055, 'Lose you', '00:03:03', 30007, 6, '2018-02-23'),
	(20056, 'Don\'t Call Me', '00:03:23', 30007, 6, '2018-02-23'),
	(20057, 'People Scare Me', '00:03:08', 30008, 7, '2017-03-05'),
	(20058, 'Love Story', '00:03:56', 30008, 7, '2017-03-05'),
	(20059, 'No Thanxxx(ft. MINO)', '00:04:37', 30008, 7, '2017-03-05'),
	(20060, 'Home Is Far Away', '00:04:51', 30008, 7, '2017-03-05'),
	(20061, 'The Benefits Of Heartbreak(ft. Lee Suhyeon)', '00:03:30', 30008, 7, '2017-03-05'),
	(20062, 'Us Against The World', '00:03:40', 30008, 7, '2017-03-05'),
	(20063, 'Lost One', '00:01:45', 30008, 7, '2017-03-05'),
	(20064, 'Sleepless', '00:01:04', 30008, 7, '2019-08-29'),
	(20065, 'In Seoul', '00:03:42', 30008, 7, '2019-08-29'),
	(20066, 'No different', '00:03:20', 30009, 7, '2019-08-29'),
	(20067, 'Lullaby For A Cat', '00:02:11', 30009, 7, '2019-08-29'),
	(20068, 'Sleeping beauty', '00:04:13', 30010, 7, '2019-10-12'),
	(20069, 'Like OOH-AHH', '00:03:35', 30000, 8, '2015-10-20'),
	(20070, 'Do it again', '00:03:26', 30000, 8, '2015-10-20'),
	(20071, 'Going crazy', '00:03:01', 30000, 8, '2015-10-20'),
	(20072, 'Truth', '00:03:33', 30000, 8, '2015-10-20'),
	(20073, 'Candy Boy', '00:02:45', 30000, 8, '2015-10-20'),
	(20074, 'Like a Fool', '00:03:34', 30000, 8, '2015-10-20'),
	(20075, 'KNOCK KCNOCK', '00:03:15', 30000, 8, '2017-02-20'),
	(20076, 'Ice Cream', '00:03:52', 30000, 8, '2017-02-20'),
	(20077, 'TT', '00:03:32', 30000, 8, '2017-02-20'),
	(20078, '1 To 100', '00:02:55', 30000, 8, '2017-02-20'),
	(20079, 'PONYTAIL', '00:03:26', 30000, 8, '2017-02-20'),
	(20080, 'JELLY JELLY', '00:03:36', 30000, 8, '2017-02-20'),
	(20081, 'As If It\'s Your Last', '00:03:34', 30000, 9, '2018-06-19'),
	(20082, 'DDU-DU-DDU-DU', '00:03:30', 30000, 9, '2018-06-19'),
	(20083, 'Forever Young', '00:03:58', 30000, 9, '2018-06-19'),
	(20084, 'Really', '00:03:18', 30000, 9, '2018-06-19'),
	(20085, 'See U Later', '00:03:19', 30000, 9, '2018-06-19'),
	(20086, 'KILL THIS LOVE', '00:03:10', 30000, 9, '2019-09-23'),
	(20087, 'Don\'t Know What To do', '00:03:22', 30000, 9, '2019-09-23'),
	(20088, 'Kick It', '00:03:12', 30000, 9, '2019-09-23'),
	(20089, 'Hope Not', '00:03:12', 30000, 9, '2019-09-23'),
	(20090, 'DDU-DU-DDU-DU(Remix)', '00:03:22', 30000, 9, '2019-09-23'),
	(20091, 'Forever Us', '00:07:13', 30011, 10, '2020-03-02'),
	(20092, 'YeongWon', '00:09:19', 30011, 10, '2020-03-02'),
	(20093, 'Giant Rabbit', '00:03:02', 30011, 10, '2020-03-02'),
	(20094, 'In Jeju', '00:07:12', 30011, 10, '2020-03-02'),
	(20095, 'Love Coding', '00:02:22', 30012, 11, '2020-09-01'),
	(20096, 'A+ Let\'s Go', '00:01:25', 30012, 11, '2020-09-01'),
	(20097, 'Coding is My Life', '00:04:44', 30012, 11, '2020-09-01'),
	(20098, 'Final exam', '00:03:22', 30012, 11, '2020-09-02'),
	(20099, 'No Copy', '00:03:17', 30012, 11, '2020-09-02'),
	(29999, 'I Will Get A+', '00:09:19', 30013, 12, '1997-09-19');
/*!40000 ALTER TABLE `song` ENABLE KEYS */;

-- 테이블 music.streaming 구조 내보내기
CREATE TABLE IF NOT EXISTS `streaming` (
  `song` int(11) NOT NULL DEFAULT 0,
  `user` int(11) NOT NULL DEFAULT 0,
  `play_time` int(11) DEFAULT 0,
  PRIMARY KEY (`song`,`user`),
  KEY `user` (`user`),
  CONSTRAINT `streaming_ibfk_2` FOREIGN KEY (`user`) REFERENCES `user` (`user_id`),
  CONSTRAINT `streaming_ibfk_3` FOREIGN KEY (`song`) REFERENCES `song` (`Song_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 music.streaming:~0 rows (대략적) 내보내기
/*!40000 ALTER TABLE `streaming` DISABLE KEYS */;
INSERT INTO `streaming` (`song`, `user`, `play_time`) VALUES
	(20003, 50006, 12),
	(20005, 50006, 1),
	(20008, 50006, 1),
	(20010, 50006, 13),
	(20011, 50008, 13),
	(20013, 50009, 44),
	(20014, 50006, 15),
	(20014, 50008, 51),
	(20015, 50008, 18),
	(20017, 50009, 31),
	(20022, 50006, 1),
	(20022, 50009, 4),
	(20033, 50009, 34),
	(20036, 50006, 11),
	(20045, 50009, 34),
	(20066, 50006, 3),
	(20077, 50006, 2),
	(20089, 50008, 5),
	(20090, 50008, 31),
	(20093, 50006, 41),
	(20097, 50008, 31);
/*!40000 ALTER TABLE `streaming` ENABLE KEYS */;

-- 테이블 music.user 구조 내보내기
CREATE TABLE IF NOT EXISTS `user` (
  `Knickname` varchar(30) NOT NULL,
  `user_id` int(11) NOT NULL AUTO_INCREMENT,
  `user_password` varchar(30) NOT NULL DEFAULT '0000',
  `user_name` varchar(15) NOT NULL,
  `sex` varchar(3) DEFAULT NULL,
  `phone_number` varchar(15) DEFAULT NULL,
  `birth_date` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`user_id`),
  UNIQUE KEY `Knickname` (`Knickname`)
) ENGINE=InnoDB AUTO_INCREMENT=50010 DEFAULT CHARSET=utf8;

-- 테이블 데이터 music.user:~0 rows (대략적) 내보내기
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` (`Knickname`, `user_id`, `user_password`, `user_name`, `sex`, `phone_number`, `birth_date`) VALUES
	('pupafafa', 50006, '1234', 'kim', 'f', '0', '0'),
	('user1', 50008, '1234', 'TOM', 'M', '010-1111-2332', '1993-09-22'),
	('user2', 50009, '1234', 'JANE', 'F', '010-7676-2332', '1993-05-11');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
