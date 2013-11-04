DECLARE @is_cdc_enabled int
SET @is_cdc_enabled = 
	(SELECT [sys].[databases].is_cdc_enabled 
		from [sys].[databases] 
		WHERE [name] = 'CoalAssay')
--/*
IF (@is_cdc_enabled = 0 )
BEGIN
	PRINT 'Enable cdc for CoalAssay'
	EXEC sys.sp_cdc_enable_db
END
ELSE
BEGIN
	PRINT 'Already enabled';
END
--*/
