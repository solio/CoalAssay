USE CoalAssay
/** ����[LoginTokens] ��*/
/** ����[LoginTokens] ��*/
--INSERT INTO [LoginTokens] ([Token], [Time]) VALUES(GETDATE(), GETDATE())
/** ����[LoginTokens] ��*/
--UPDATE [LoginTokens] SET Token = HASHBYTES('MD5', '111222') WHERE Token = '11  4 2013  8:21PM'
/** ɾ��[LoginTokens] �����*/
--DELETE  FROM [LoginTokens]

--SELECT * FROM [LoginTokens]

--SELECT * 
--FROM CHANGETABLE(CHANGES dbo.LoginTokens,0) as ct

EXEC sys.sp_cdc_enable_table
@source_schema = 'dbo',  
@source_name = 'LoginTokens',  
@role_name = NULL,  
@capture_instance = 'hello',  
@supports_net_changes = 1,  
@index_name = NULL,  
@captured_column_list = NULL,  
@filegroup_name = default 

--EXEC sys.sp_cdc_disable_table
--@source_schema = 'dbo',  
--@source_name = 'LoginTokens',  
--@capture_instance = 'hello'