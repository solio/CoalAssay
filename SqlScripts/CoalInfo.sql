/*
   2013年11月3日12:54:47
   用户: 
   服务器: SOLIO-PC\SOLIO
   数据库: CoalAssay
   应用程序: 
*/

/* 为了防止任何可能出现的数据丢失问题，您应该先仔细检查此脚本，然后再在数据库设计器的上下文之外运行此脚本。*/
BEGIN TRANSACTION
SET QUOTED_IDENTIFIER ON
SET ARITHABORT ON
SET NUMERIC_ROUNDABORT OFF
SET CONCAT_NULL_YIELDS_NULL ON
SET ANSI_NULLS ON
SET ANSI_PADDING ON
SET ANSI_WARNINGS ON
COMMIT
BEGIN TRANSACTION
GO
CREATE TABLE dbo.CoalInfo
	(
	ID int NOT NULL IDENTITY (1, 1),
	BatchNumber nvarchar(20) NOT NULL,
	AssayCode nvarchar(20) NOT NULL,
	AssayDate date NOT NULL,
	ComingDate date NOT NULL,
	AssayType tinyint NOT NULL,
	Assayer nvarchar(20) NOT NULL,
	Submitor nvarchar(20) NULL,
	Stage nchar(10) NULL,
	Manufacturer nvarchar(50) NOT NULL
	)  ON [PRIMARY]
GO
DECLARE @v sql_variant 
SET @v = N'接受批号'
EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'CoalInfo', N'COLUMN', N'BatchNumber'
GO
ALTER TABLE dbo.CoalInfo ADD CONSTRAINT
	PK_CoalInfo PRIMARY KEY CLUSTERED 
	(
	ID
	) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

GO
ALTER TABLE dbo.CoalInfo SET (LOCK_ESCALATION = TABLE)
GO
COMMIT
select Has_Perms_By_Name(N'dbo.CoalInfo', 'Object', 'ALTER') as ALT_Per, Has_Perms_By_Name(N'dbo.CoalInfo', 'Object', 'VIEW DEFINITION') as View_def_Per, Has_Perms_By_Name(N'dbo.CoalInfo', 'Object', 'CONTROL') as Contr_Per 