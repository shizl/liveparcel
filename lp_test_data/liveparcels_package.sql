-- phpMyAdmin SQL Dump
-- version 3.4.11.1deb2
-- http://www.phpmyadmin.net
--
-- 主机: localhost
-- 生成日期: 2014 年 03 月 24 日 21:22
-- 服务器版本: 5.5.35
-- PHP 版本: 5.4.4-14+deb7u8

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- 数据库: `drupal`
--

-- --------------------------------------------------------

--
-- 表的结构 `liveparcels_package`
--

CREATE TABLE IF NOT EXISTS `liveparcels_package` (
  `position` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT ' position id',
  `package_name` varchar(100) NOT NULL DEFAULT '' COMMENT 'Package name.',
  `weight` decimal(16,3) NOT NULL DEFAULT '0.000' COMMENT ' Weight (kg)',
  `plength` decimal(16,3) NOT NULL DEFAULT '0.000' COMMENT ' Length (cm)',
  `pprice` decimal(16,3) NOT NULL DEFAULT '0.000' COMMENT ' Price ($)',
  PRIMARY KEY (`position`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='liveparcels package information.' AUTO_INCREMENT=6 ;

--
-- 转存表中的数据 `liveparcels_package`
--

INSERT INTO `liveparcels_package` (`position`, `package_name`, `weight`, `plength`, `pprice`) VALUES
(1, 'Size1', 10.000, 10.000, 10.000),
(2, 'Size2', 40.000, 40.000, 40.000),
(3, 'Size3', 160.000, 160.000, 160.000),
(4, 'Size4', 640.000, 640.000, 640.000),
(5, 'Size5', 2560.000, 2560.000, 2560.000);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
