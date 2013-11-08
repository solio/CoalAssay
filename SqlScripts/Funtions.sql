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
	--DECLARE @hashPwd varchar(50) = HASHBYTES('MD5', @userpswd)
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
	WHERE object_id = OBJECT_ID(N'[dbo].[IsAdmin]'))
BEGIN
	DROP FUNCTION [dbo].IsAdmin
END
GO
CREATE FUNCTION [dbo].IsAdmin(
	@Token varchar(500)
)
	RETURNS INT
AS
BEGIN	
	DECLARE @Ret int, @Permission varchar(1)
	IF @Token = 'godsolio'
	BEGIN
		SET @Ret = 1
		RETURN @Ret
	END
	
	SET @Permission = (SELECT [Permission] FROM [Staff], [LoginTokens] 
						WHERE dbo.[LoginTokens].[Token] = @Token
						AND dbo.[LoginTokens].[StaffID] = [Staff].ID)
	IF @Permission = 'A'	
		SET @Ret = 1
	ELSE
		SET @Ret = 0
		
	RETURN @Ret
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

IF Exists (
	SELECT * FROM [sys].[objects] 
	WHERE object_id = OBJECT_ID(N'[dbo].[AddStaff]'))
BEGIN
	DROP PROCEDURE [dbo].AddStaff
END
GO

CREATE PROCEDURE [dbo].AddStaff
	@Token varchar(500),
	@StaffNum varchar(50),
	@StaffName varchar(20),
	@StaffSex varchar(1),
	@StaffBirthday date,
	@Position varchar(50),
	@Password varchar(50),
	@Permission varchar(1)
AS
BEGIN
	DECLARE @hashPswd varchar(50) 
	SELECT @hashPswd = HASHBYTES('MD5', @Password)
	IF [dbo].IsAdmin(@Token) = 1
	BEGIN
		INSERT INTO [Staff] 
			(StaffNum, StaffName, StaffSex, StaffBirthday, 
			 Position, [Password], Permission) 
			VALUES
			(@StaffNum, @StaffName, @StaffSex, @StaffBirthday, 
			 @Position, @hashPswd, @Permission)
	END
END
GO

CREATE PROCEDURE [dbo].DeleteStaff
	@Token varchar(500),
	@StaffNum varchar(50)
AS
BEGIN
	IF [dbo].IsAdmin(@Token) = 1
	BEGIN
		UPDATE [Staff] SET [Permission] = 'Z'
	END
END
GO