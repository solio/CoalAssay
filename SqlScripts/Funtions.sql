CREATE FUNCTION [dbo].Login(
	@username nvarchar(20),
	@userpswd nvarchar(20)
)
	RETURNS nvarchar(50)
AS
BEGIN
	DECLARE @Token nvarchar(50), @ret int
	SET @ret = (SELECT COUNT(*) FROM [dbo].[Staff] 
		WHERE [StaffName] = @username 
		AND [Password] = @userpswd)
	IF @ret = 1
	BEGIN
		SET @Token = hashbytes('MD5', @username + @userpswd)
	END
	ELSE
	BEGIN
		SET @Token = 'ERROR'
	END
	
	RETURN @Token
END

GO

--CREATE FUNCTION 