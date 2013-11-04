IF Exists (
	SELECT * FROM [sys].[objects] 
	WHERE object_id = OBJECT_ID(N'[dbo].[Login]') AND type in (N'FN', N'IF', N'TF', N'FS', N'FT'))
BEGIN
	PRINT 'FUNCTINO Login uninstall'
	DROP FUNCTION [dbo].Login
END
ELSE
BEGIN
	PRINT 'FUNCTION Login not exists'
END
