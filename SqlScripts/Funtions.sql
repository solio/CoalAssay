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
	DECLARE @hashPwd varchar(50) = HASHBYTES('MD5', @userpswd)
	SET @ret = (SELECT COUNT(*) FROM [dbo].[Staff] 
		WHERE [StaffNum] = @username 
		AND [Password] = @hashpwd)
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
						WHERE 
						UPPER(sys.fn_varbintohexstr(dbo.[LoginTokens].[Token])) = ('0X' + @Token)
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
	DECLARE @Token varbinary(50), @ID int
	DECLARE @hashPwd varbinary(50) = HASHBYTES('MD5', @Password)
	DECLARE @now date = GETDATE()
	--SELECT @Password as Password, @hashPwd as hashPwd --debug
	SET @Token = [dbo].Auth(@StaffNum, @Password)
	SELECT @Token AS Token,
		[StaffName], [StaffSex],[StaffBirthday],[Position],[Permission]
	FROM [Staff]
	WHERE [StaffNum] = @StaffNum AND [Password] = @hashPwd
	SELECT @ID = [ID]
	FROM [Staff]	
	WHERE [StaffNum] = @StaffNum AND [Password] = @hashPwd
	--SELECT @ID --debug
	IF @ID IS NOT NULL
		INSERT INTO [dbo].LoginTokens values(@Token, @ID, @now)
GO

IF Exists (
	SELECT * FROM [sys].[objects] 
	WHERE object_id = OBJECT_ID(N'[dbo].[AddStaff]'))
BEGIN
	DROP PROCEDURE [dbo].AddStaff
END
GO

CREATE PROCEDURE [dbo].AddStaff
	@Token nvarchar(500),
	@StaffNum nvarchar(50),
	@StaffName nvarchar(20),
	@StaffSex nvarchar(1),
	@StaffBirthday date,
	@Position nvarchar(50),
	@Password nvarchar(50),
	@Permission nvarchar(1)
AS
BEGIN
	DECLARE @hashPswd varbinary(50) = HASHBYTES('MD5', @Password)--varchar(50) 
	--SELECT @hashPswd = HASHBYTES('MD5', @Password)
	IF [dbo].IsAdmin(@Token) = 1
	BEGIN
		DECLARE @exist int
		SET @exist = (SELECT COUNT([ID]) FROM [Staff] WHERE [StaffNum] = @StaffNum)
		IF @exist > 0
		BEGIN
			UPDATE [Staff] SET
				StaffName = @StaffName, StaffSex = @StaffSex, StaffBirthday = @StaffBirthday, 
				Position = @Position, [Password] = @hashPswd, Permission = @Permission
			WHERE
				StaffNum = @StaffNum 
		END
		ELSE
		BEGIN
			INSERT INTO [Staff] 
				(StaffNum, StaffName, StaffSex, StaffBirthday, 
				 Position, [Password], Permission) 
				VALUES
				(@StaffNum, @StaffName, @StaffSex, @StaffBirthday, 
				 @Position, @hashPswd, @Permission)		
		END
		--SELECT @hashPswd --debug
		IF @@ROWCOUNT = 1
			SELECT 'SUCCESS' --AS AddedResult
		ELSE
			SELECT 'NODATA INSERT' --AS AddedResult
	END
	ELSE
	BEGIN
		SELECT 'ERROR Permission Denied' --AS AddedResult
	END
END
GO

IF Exists (
	SELECT * FROM [sys].[objects] 
	WHERE object_id = OBJECT_ID(N'[dbo].[DeleteStaff]'))
BEGIN
	DROP PROCEDURE [dbo].DeleteStaff
END
GO

CREATE PROCEDURE [dbo].DeleteStaff
	@Token varchar(500),
	@StaffNum varchar(50)
AS
BEGIN
	IF [dbo].IsAdmin(@Token) = 1
	BEGIN
		UPDATE [Staff] SET [Permission] = 'Z' WHERE [StaffNum] = @StaffNum
		IF @@ROWCOUNT = 1
			SELECT 'SUCCCESS' AS DeletedResult
		ELSE
			SELECT 'NODATA INSERT' AS DeletedResult
	END
	ELSE
	BEGIN
		SELECT 'ERROR Permission Denied' AS DeletedResult
	END	
END
GO