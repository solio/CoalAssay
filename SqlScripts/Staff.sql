/*
   2013年11月3日11:33:33
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
CREATE TABLE dbo.Staff
	(
	ID int NOT NULL IDENTITY (1, 1),
	Name nvarchar(10) NOT NULL,
	Sex bit NOT NULL,
	Age int NOT NULL,
	Post nvarchar(50) NOT NULL
	)  ON [PRIMARY]
GO
DECLARE @v sql_variant 
SET @v = N'0女 1男'
EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Staff', N'COLUMN', N'Sex'
GO
ALTER TABLE dbo.Staff ADD CONSTRAINT
	PK_Staff PRIMARY KEY CLUSTERED 
	(
	ID
	) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

GO
ALTER TABLE dbo.Staff SET (LOCK_ESCALATION = TABLE)
GO
COMMIT
select Has_Perms_By_Name(N'dbo.Staff', 'Object', 'ALTER') as ALT_Per, Has_Perms_By_Name(N'dbo.Staff', 'Object', 'VIEW DEFINITION') as View_def_Per, Has_Perms_By_Name(N'dbo.Staff', 'Object', 'CONTROL') as Contr_Per 