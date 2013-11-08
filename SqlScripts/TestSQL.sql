USE CoalAssay
/** 测试[LoginTokens] 表*/
/** 插入[LoginTokens] 表*/
--INSERT INTO [LoginTokens] ([Token], [Time]) VALUES(GETDATE(), GETDATE())
/** 更新[LoginTokens] 表*/
--UPDATE [LoginTokens] SET Token = HASHBYTES('MD5', '111222') WHERE Token = '11  4 2013  8:21PM'
/** 删除[LoginTokens] 表测试*/
--DELETE  FROM [LoginTokens]

--SELECT * FROM [LoginTokens]

--SELECT * 
--FROM CHANGETABLE(CHANGES dbo.LoginTokens,0) as ct

--EXEC sys.sp_cdc_enable_table
--@source_schema = 'dbo',  
--@source_name = 'LoginTokens',  
--@role_name = NULL,  
--@capture_instance = 'hello',  
--@supports_net_changes = 1,  
--@index_name = NULL,  
--@captured_column_list = NULL,  
--@filegroup_name = default 

--EXEC sys.sp_cdc_disable_table
--@source_schema = 'dbo',  
--@source_name = 'LoginTokens',  
--@capture_instance = 'hello'

--DECLARE @changes TABLE
--SET @changes = cdc.fn_cdc_get_all_changes_dbo_LoginTokens()

/** 测试约束 **/
--SELECT * FROM CoalInfo
--INSERT INTO [AshFusionPoint] VALUES(1,1,1.00,1.00,1.00,1.00)

/** 测试Auth函数**/
--SELECT COUNT(*) FROM [dbo].[Staff] 
--		WHERE [StaffNum] = '1232'
--		AND [Password] = 'afdg23'
--SELECT dbo.Auth('1232', 'afdg23')
EXEC [dbo].Login '1232', 'afdg23'

--SELECT CONVERT(varchar, GETDATE(),20)

/** 测试加密**/
DECLARE @ClearPWD varchar(255) ,@pwd varchar(255) 
DECLARE @EncryptedPWD varbinary(255),@pwdBinary varbinary(255)
SELECT @ClearPWD = 'ADSFDAteARFst' 
SELECT @EncryptedPWD = CONVERT(varbinary(255), HASHBYTES('MD5', @ClearPWD))
SELECT @EncryptedPWD
DECLARE @pwdString varchar(255)--= CONVERT(varbinary(255), '0x229EC0B72316448782B54987D5438007')
--SELECT @pwdBinary = CONVERT(varbinary(255), HASHBYTES('MD5',@ClearPWD)) 
--SELECT @pwdBinary
--IF @EncryptedPWD = @pwdBinary
--	PRINT 'EQUAL'
--ELSE
--	PRINT 'NOT EQUAL'
SELECT @pwdString = HASHBYTES('MD5', @ClearPWD)
IF @EncryptedPWD = @pwdString
	PRINT 'EQUAL'
ELSE
	PRINT 'NOT EQUAL'
--SELECT @pwd = CONVERT(nvarchar(255), @EncryptedPWD)
--SELECT @pwd