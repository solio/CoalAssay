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
--EXEC [dbo].Login '1232', 'afdg23'

--SELECT CONVERT(varchar, GETDATE(),20)

/** 测试加密**/
--DECLARE @ClearPWD varchar(255) ,@pwd varchar(255) 
--DECLARE @EncryptedPWD varbinary(255),@pwdBinary varbinary(255)
--SELECT @ClearPWD = 'w36308458' 
--SELECT @EncryptedPWD = CONVERT(varbinary(255), HASHBYTES('MD5', @ClearPWD))
--SELECT @EncryptedPWD as EncryptedPWD
--DECLARE @pwdString varchar(255)--= CONVERT(varbinary(255), '0x229EC0B72316448782B54987D5438007')
--SELECT @pwdBinary = CONVERT(varbinary(255), HASHBYTES('MD5',@ClearPWD)) 
--SELECT @pwdBinary as pwdBinary
--IF @EncryptedPWD = @pwdBinary
--	PRINT 'EQUAL'
--ELSE
--	PRINT 'NOT EQUAL'
--SELECT @pwdString = HASHBYTES('MD5', @ClearPWD)
--IF @EncryptedPWD = @pwdString
--	PRINT 'EQUAL'
--ELSE
--	PRINT 'NOT EQUAL'
--SELECT @pwd = CONVERT(nvarchar(255), @EncryptedPWD)
--SELECT @pwdString as pwdString

/** 添加用户测试**/
--SELECT ISNUMERIC('0123123323');
--EXEC [dbo].AddStaff 'godsolio','041030233','夏治道','1','1991-06-09','班长','w36308458','A'
--DECLARE @realPwd varbinary(50)
--SELECT @realPwd = [Password]  FROM Staff WHERE [StaffNum] = '041030233'
--SELECT @realPwd as realPwd
--DECLARE @Pswd nvarchar(255) = Convert(nvarchar(255),HASHBYTES('MD5', 'w36308458'))
--SELECT @Pswd
--DECLARE @hashPwd varbinary(50) = HASHBYTES('MD5', 'w36308458')	
--SELECT [dbo].Auth('041030233', 'w36308458') AS Token,
--	[StaffName], [StaffSex],[StaffBirthday],[Position],[Permission]
--FROM [Staff]
--WHERE [StaffNum] = '041030233' AND [Password] = @hashPwd
--SELECT @hashPwd as hashPwd

--EXEC [dbo].Login '041030233','w36308458'

--if @hashPwd = @realPwd
--	PRINT 'EQUAL'
	
/** 删除用户测试**/
--EXEC [dbo].DeleteStaff 'sdfadfad', '1232'
--EXEC [dbo].Login '1232','afdg23'
--DECLARE @ID int
--SELECT COUNT(*)--@ID = [ID]
--	FROM [Staff]	
--	WHERE [StaffNum] = '1232' AND [Password] = 'afdg23'
--SELECT @ID

--DECLARE @Token varbinary(255), @TokenString nvarchar(255)
--DECLARE @Ret int, @Permission varchar(1)
--SET @Token = [dbo].Auth('041030233', 'w36308458')
--SET @Permission = (SELECT [Permission] FROM [Staff], [LoginTokens] 
--					WHERE dbo.[LoginTokens].[Token] = @Token
--					AND dbo.[LoginTokens].[StaffID] = [Staff].ID)
--SELECT @TokenString = UPPER(sys.fn_varbintohexstr(@Token))
--SELECT @TokenString
--SELECT @Token
--SELECT @Permission as Permission
--IF @TokenString = '0X41DF61F07564046C179D477BF4694DAD'
--	PRINT 'EQUAL'
--ELSE
--	PRINT 'NOT EQUAL'
--DECLARE @msg nvarchar(50)
--EXEC [dbo].AddStaff 
--	'41DF61F07564046C179D477BF4694DAD',
--	'041030234',
--	'NewStaff',
--	'1',
--	'2013-11- 9',
--	'一般员工',
--	'w36308458',
--	'B'
--EXEC [dbo].DeleteStaff '41DF61F07564046C179D477BF4694DAD', '041030234'

--EXEC [dbo].AddStaff 
--	'D322AA1D23AFD8ECC251DFB73D604F33',
--	'041030234',
--	'NewStaff',
--	'1',
--	'2013-11- 9',
--	'一般员工',
--	'w36308458',
--	'B'
--EXEC [dbo].DeleteStaff '41DF61F07564046C179D477BF4694DAD', '041030234'

/** 测试跟踪操作**/
EXEC [dbo].Track 'token test', 'SELECT', 'Login', 'SUCCESS'