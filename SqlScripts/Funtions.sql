USE CoalAssay

IF Exists (
	SELECT * FROM [sys].[objects] 
	WHERE object_id = OBJECT_ID(N'[dbo].[Auth]'))
BEGIN
	DROP FUNCTION [dbo].Auth
END

GO

CREATE FUNCTION [dbo].Auth(
	@username nvarchar(20),
	@userpswd nvarchar(20)
)
	--RETURNS nvarchar(50)
	RETURNS VARBINARY(500)
AS
BEGIN
	DECLARE @Token varbinary(500), @ret int, @now date
	SET @ret = (SELECT COUNT(*) FROM [dbo].[Staff] 
		WHERE [StaffNum] = @username 
		AND [Password] = @userpswd)
	SET @now = GETDATE()
	IF @ret = 1
	BEGIN
		SET @Token = hashbytes('MD5', @username + @userpswd + CONVERT(varchar, @now, 20))
	END
	ELSE
	BEGIN
		SET @Token = CONVERT(varbinary(500),'ERROR')
	END
	
	RETURN @Token
END
GO


IF Exists (
	SELECT * FROM [sys].[objects] 
	WHERE object_id = OBJECT_ID(N'[dbo].[Login]'))
BEGIN
	DROP PROCEDURE [dbo].Login
END
GO

CREATE PROCEDURE [dbo].Login 
	@StaffNum nvarchar(50),
	@Password nvarchar(50)
AS
	SELECT [dbo].Auth(@StaffNum, @Password) AS Token,
		[StaffName], [StaffSex],[StaffBirthday],[Position],[Permission]
	FROM [Staff]
	WHERE [StaffNum] = @StaffNum AND [Password] = @Password

GO