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
	WHERE object_id = OBJECT_ID(N'[dbo].[Track]'))
BEGIN
	DROP PROCEDURE [dbo].Track
END
GO

CREATE PROCEDURE [dbo].Track(
	@Token nvarchar(50),
	@Operation nvarchar(50),	
	@Dest nvarchar(50),
	@Note nvarchar(50)
)
AS
BEGIN
	DECLARE @Now DATETIME = GETDATE()
	INSERT INTO [dbo].OperationTrack 
		([Token], [Operation], [Dest], [Time], [Note])
	VALUES(
		@Token, @Operation, @Dest, @Now, @Note
	)
	RETURN @@ROWCOUNT
END
GO

IF Exists (
	SELECT * FROM [sys].[objects] 
	WHERE object_id = OBJECT_ID(N'[dbo].[Login]'))
BEGIN
	DROP PROCEDURE [dbo].Login
END
GO

--用户相关存储过程--
CREATE PROCEDURE [dbo].Login 
	@StaffNum nvarchar(50),
	@Password nvarchar(50)
AS
	DECLARE @Token varbinary(50)
	DECLARE @hashPwd varbinary(50) = HASHBYTES('MD5', @Password)
	DECLARE @ID int, @now DATETIME = GETDATE()	
	--SELECT @Password as Password, @hashPwd as hashPwd --debug
	SET @Token = [dbo].Auth(@StaffNum, @Password)
	DECLARE @TokenString nvarchar(50) = UPPER(sys.fn_varbintohexstr(@Token))
	SELECT @Token AS Token,
		[StaffName], [StaffSex],[StaffBirthday],[Position],[Permission]
	FROM [Staff]
	WHERE [StaffNum] = @StaffNum AND [Password] = @hashPwd AND [Permission] <> 'Z'
	SELECT @ID = [ID]
	FROM [Staff]	
	WHERE [StaffNum] = @StaffNum AND [Password] = @hashPwd AND [Permission] <> 'Z'
	--SELECT @ID --debug
	IF @ID IS NOT NULL
	BEGIN
		INSERT INTO [dbo].LoginTokens VALUES(@Token, @ID, @now)
		EXEC [dbo].Track @TokenString, 'Select', 'Login', 'SUCCESS'
	END
	ELSE
		EXEC [dbo].Track @TokenString, 'Select', 'Login', 'ERROR'
GO

IF Exists (
	SELECT * FROM [sys].[objects] 
	WHERE object_id = OBJECT_ID(N'[dbo].[AddStaff]'))
BEGIN
	DROP PROCEDURE [dbo].AddStaff
END
GO

CREATE PROCEDURE [dbo].AddStaff
	@Token nvarchar(50),
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
	DECLARE @now DATETIME = GETDATE()
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
			IF @@ROWCOUNT = 1
			BEGIN
				SELECT 'SUCCESS' AS AddedResult
				EXEC [dbo].Track @Token, 'INSERT', 'AddStaff', 'SUCCESS Exist Before'
			END
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
		BEGIN
			SELECT 'SUCCESS' AS AddedResult
			EXEC [dbo].Track @Token, 'INSERT', 'AddStaff', 'SUCCESS Not Exist Before'
		END
		ELSE
		BEGIN
			SELECT 'NODATA INSERT' AS AddedResult
			EXEC [dbo].Track @Token, 'INSERT', 'AddStaff', 'ERROR NODATA INSERT'
		END
	END
	ELSE
	BEGIN
		SELECT 'ERROR Permission Denied' AS AddedResult
		EXEC [dbo].Track @Token, 'INSERT', 'AddStaff', 'ERROR Permission Denied'
	END
END
GO

IF Exists (
	SELECT * FROM [sys].[objects] 
	WHERE object_id = OBJECT_ID(N'[dbo].[EditStaff]'))
BEGIN
	DROP PROCEDURE [dbo].EditStaff
END
GO

CREATE PROCEDURE [dbo].EditStaff
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
	DECLARE @Token nvarchar(255)	
	UPDATE [Staff] SET
		StaffName = @StaffName, StaffSex = @StaffSex, StaffBirthday = @StaffBirthday, 
		Position = @Position, [Password] = @hashPswd, Permission = @Permission
		WHERE [StaffNum] = @StaffNum
	IF @@ROWCOUNT = 1
	BEGIN
		SELECT @Token = [Token] FROM [Staff],[LoginTokens] 
			WHERE [StaffNum] = @StaffNum AND [Staff].ID = [LoginTokens].StaffID
		SELECT 'SUCCESS' --AS AddedResult
		EXEC [dbo].Track @Token, 'UPDATE','EditStaff', 'SUCCESS'
	END
	ELSE
	BEGIN
		SELECT 'NODATA UPDATED' --AS AddedResult
		EXEC [dbo].Track 'WRONG', 'UPDATE','EditStaff', 'ERROR NODATA UPDATED'
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
		BEGIN
			SELECT 'SUCCCESS' AS DeletedResult
			EXEC [dbo].Track @Token,'DELETE','DeleteStaff', 'SUCCESS'
		END
		ELSE
		BEGIN
			SELECT 'NODATA DELETED' AS DeletedResult
			EXEC [dbo].Track @Token,'DELETE','DeleteStaff', 'ERROR NODATA DELETED'
		END
	END
	ELSE
	BEGIN
		SELECT 'ERROR Permission Denied' AS DeletedResult
		EXEC [dbo].Track @Token,'DELETE','DeleteStaff', 'ERROR Permission Denied'
	END	
END
GO

IF Exists (
	SELECT * FROM [sys].[objects] 
	WHERE object_id = OBJECT_ID(N'[dbo].[SelectAllStaff]'))
BEGIN
	DROP PROCEDURE [dbo].SelectAllStaff
END
GO

CREATE PROCEDURE [dbo].SelectAllStaff
	@Token varchar(50)
AS
BEGIN
	--DECLARE @IsToken nchar(1)
	--SET @IsToken = (SELECT [Permission] FROM [Staff], [LoginTokens] 
	--				WHERE 
	--					UPPER(sys.fn_varbintohexstr(dbo.[LoginTokens].[Token])) = ('0X' + @Token)
	--					AND dbo.[LoginTokens].[StaffID] = [Staff].ID)	
	IF [dbo].IsAdmin(@Token) = 1
	BEGIN
		SELECT [StaffNum],[StaffName],[StaffSex],[StaffBirthday],[Position],[Permission]
			FROM [Staff] WHERE [Permission] <> 'Z'
		EXEC [dbo].Track @Token,'SELECT','SelectAllStaff', 'SUCCESS'
	END
	ELSE
	BEGIN
		SELECT 'ERROR Permission Denied' AS SELECTALLRESULT
		EXEC [dbo].Track @Token,'SELECT','SelectAllStaff', 'ERROR Permission Denied'
	END
END
GO

--CoalInfo相关存储--
IF Exists (
	SELECT * FROM [sys].[objects] 
	WHERE object_id = OBJECT_ID(N'[dbo].[AddCoalInfo]'))
BEGIN
	DROP PROCEDURE [dbo].AddCoalInfo
END
GO

CREATE PROCEDURE [dbo].AddCoalInfo
	@Token varchar(50)
	,@CoalLotNum	nvarchar(20)
	,@AssayCode	nvarchar(20)
	,@AssayDate	datetime
	,@SampleDate	datetime
	,@AssayType	tinyint
	,@AssayStaff	nvarchar(20)
	,@SampleStaff	nvarchar(20)
	,@StageName	nvarchar(50)
	,@WorksName	nvarchar(50)
AS
BEGIN
	IF [dbo].IsAdmin(@Token) = 1
	BEGIN
		INSERT INTO [CoalAssay].[dbo].[CoalInfo]
			([CoalLotNum],[AssayCode],[AssayDate],[SampleDate],[AssayType],
			 [AssayStaff],[SampleStaff],[StageName],[WorksName])
		VALUES
		   (@CoalLotNum,@AssayCode,@AssayDate,@SampleDate,@AssayType
		   ,@AssayStaff,@SampleStaff,@StageName,@WorksName)		
		EXEC [dbo].Track @Token,'INSERT','AddCoalInfo', 'SUCCESS'
	END
	ELSE
	BEGIN
		SELECT 'ERROR Permission Denied' AS SELECTALLRESULT
		EXEC [dbo].Track @Token,'INSERT','AddCoalInfo', 'ERROR Permission Denied'
	END	
END
GO

IF Exists (
	SELECT * FROM [sys].[objects] 
	WHERE object_id = OBJECT_ID(N'[dbo].[SelectUnChecked]'))
BEGIN
	DROP PROCEDURE [dbo].SelectUnChecked
END
GO

CREATE PROCEDURE [dbo].SelectUnChecked
	@Token varchar(50)
AS
BEGIN
	IF [dbo].IsAdmin(@Token) = 1
	BEGIN
		SELECT 
			 [CoalLotNum],[AssayCode],[AssayDate],[SampleDate],[AssayType],
			 [AssayStaff],[SampleStaff],[StageName],[WorksName]
		FROM
			[CoalInfo]
		WHERE [State] = 0
		EXEC [dbo].Track @Token,'SELECT','SelectUnChecked', 'SUCCESS'
	END
	ELSE
	BEGIN
		SELECT 'ERROR Permission Denied' AS SELECTALLRESULT
		EXEC [dbo].Track @Token,'SELECT','SelectUnChecked', 'ERROR Permission Denied'
	END	
END
GO

IF Exists (
	SELECT * FROM [sys].[objects] 
	WHERE object_id = OBJECT_ID(N'[dbo].[CheckTask]'))
BEGIN
	DROP PROCEDURE [dbo].CheckTask
END
GO

CREATE PROCEDURE [dbo].CheckTask
	@Token varchar(50)
	,@wcsAssayCode	nvarchar(20)
	,@State	int		
AS
BEGIN
	IF [dbo].IsAdmin(@Token) = 1
	BEGIN
		UPDATE [CoalInfo] SET [State] = @State WHERE [AssayCode] = @wcsAssayCode 
		EXEC [dbo].Track @Token,'UPDATE','CheckTask', 'SUCCESS'
	END
	ELSE
	BEGIN
		SELECT 'ERROR Permission Denied' AS SELECTALLRESULT
		EXEC [dbo].Track @Token,'UPDATE','CheckTask', 'ERROR Permission Denied'
	END	
END
GO

IF Exists (
	SELECT * FROM [sys].[objects] 
	WHERE object_id = OBJECT_ID(N'[dbo].[SearchCoal]'))
BEGIN
	DROP PROCEDURE [dbo].SearchCoal
END
GO

CREATE PROCEDURE [dbo].SearchCoal
	@Token varchar(50)
	,@Condition nvarchar(20)
	,@AssayCode	nvarchar(20)
	,@AssayStaff nvarchar(20)
	,@BeginDate date
	,@EndDate date
AS
BEGIN
	IF [dbo].IsAdmin(@Token) = 1
	BEGIN
		IF @Condition = 'AssayCode'
		BEGIN
			SELECT 
				[CoalLotNum],[CoalInfo].[AssayCode],[CoalInfo].[AssayDate],
				[SampleDate],[AssayType],[CoalInfo].[AssayStaff],[SampleStaff],
				[StageName],[WorksName]
			FROM [CoalInfo] WHERE [AssayCode] = @AssayCode
			SELECT 
				[Qb_ad],[Qgr_d],[Qgr_a],[Qnet_ar]
			FROM CaloriMeter WHERE [AssayCode] = @AssayCode
			SELECT 
				[AshFusionT1],[AshFusionT2],[AshFusionT3],[AshFusionT4]
			FROM AshFusionPoint WHERE [AssayCode] = @AssayCode
			SELECT 
				[Had]
			FROM ElementAnalyzer WHERE [AssayCode] = @AssayCode
			SELECT 
				[Mar]
			FROM LightWaveMeter WHERE [AssayCode] = @AssayCode
			SELECT 
				[St_ad],[St_d]
			FROM SulfurDetector WHERE [AssayCode] = @AssayCode
			SELECT 
				[Vd],[Vad],[Var],[Vdaf],[Mad],[Aad],[Aar]
			FROM WorkPointInstrument WHERE [AssayCode] = @AssayCode												
					
			--SELECT Top 1	 
			--	[CoalLotNum],[CoalInfo].[AssayCode],[CoalInfo].[AssayDate],[SampleDate],[AssayType],[CoalInfo].[AssayStaff],[SampleStaff],[StageName],[WorksName]
			--	,[Qb_ad],[Qgr_d],[Qgr_a],[Qnet_ar]
			--	,[AshFusionT1],[AshFusionT2],[AshFusionT3],[AshFusionT4]
			--	,[Had]
			--	,[Mar]
			--	,[St_ad],[St_d]
			--	,[Vd],[Vad],[Var],[Vdaf],[Mad],[Aad],[Aar]
			--FROM
			--	[CoalInfo]
			--	LEFT JOIN [CaloriMeter] ON [CoalInfo].AssayCode=@AssayCode AND [CoalInfo].AssayCode=[CaloriMeter].AssayCode
			--	LEFT JOIN [AshFusionPoint] ON [CoalInfo].AssayCode=[AshFusionPoint].AssayCode
			--	LEFT JOIN [ElementAnalyzer] ON [CoalInfo].AssayCode=[ElementAnalyzer].AssayCode
			--	LEFT JOIN [LightWaveMeter] ON [CoalInfo].AssayCode=[LightWaveMeter].AssayCode
			--	LEFT JOIN [SulfurDetector] ON [CoalInfo].AssayCode=[SulfurDetector].AssayCode
			--	LEFT JOIN [WorkPointInstrument] ON [CoalInfo].AssayCode=[WorkPointInstrument].AssayCode
			EXEC [dbo].Track @Token,'SELECT','SearchCoal', 'SUCCESS'			
		END
		ELSE IF @Condition = 'Staff'			
		BEGIN
			SELECT
				[CoalLotNum],[CoalInfo].[AssayCode],[CoalInfo].[AssayDate],[SampleDate],[AssayType],[CoalInfo].[AssayStaff],[SampleStaff],[StageName],[WorksName]
				,[Qb_ad],[Qgr_d],[Qgr_a],[Qnet_ar]
				,[AshFusionT1],[AshFusionT2],[AshFusionT3],[AshFusionT4]
				,[Had]
				,[Mar]
				,[St_ad],[St_d]
				,[Vd],[Vad],[Var],[Vdaf],[Mad],[Aad],[Aar]
			FROM
				[CoalInfo] 
				LEFT JOIN [CaloriMeter] ON [CoalInfo].AssayStaff=@AssayStaff AND [CoalInfo].AssayCode=[CaloriMeter].AssayCode
				LEFT JOIN [AshFusionPoint] ON [CoalInfo].AssayCode=[AshFusionPoint].AssayCode
				LEFT JOIN [ElementAnalyzer] ON [CoalInfo].AssayCode=[ElementAnalyzer].AssayCode
				LEFT JOIN [LightWaveMeter] ON [CoalInfo].AssayCode=[LightWaveMeter].AssayCode
				LEFT JOIN [SulfurDetector] ON [CoalInfo].AssayCode=[SulfurDetector].AssayCode
				LEFT JOIN [WorkPointInstrument] ON [CoalInfo].AssayCode=[WorkPointInstrument].AssayCode		
			EXEC [dbo].Track @Token,'SELECT','SearchCoal', 'SUCCESS'			
		END
		ELSE IF @Condition = 'Date'			
		BEGIN
			SELECT
				[CoalLotNum],[CoalInfo].[AssayCode],[CoalInfo].[AssayDate],[SampleDate],[AssayType],[CoalInfo].[AssayStaff],[SampleStaff],[StageName],[WorksName]
				,[Qb_ad],[Qgr_d],[Qgr_a],[Qnet_ar]
				,[AshFusionT1],[AshFusionT2],[AshFusionT3],[AshFusionT4]
				,[Had]
				,[Mar]
				,[St_ad],[St_d]
				,[Vd],[Vad],[Var],[Vdaf],[Mad],[Aad],[Aar]
			FROM
				[CoalInfo]
				LEFT JOIN [CaloriMeter] ON [CoalInfo].AssayDate<=@EndDate 
						  AND [CoalInfo].AssayDate >= @BeginDate 
						  AND [CoalInfo].AssayCode=[CaloriMeter].AssayCode
				LEFT JOIN [AshFusionPoint] ON [CoalInfo].AssayCode=[AshFusionPoint].AssayCode
				LEFT JOIN [ElementAnalyzer] ON [CoalInfo].AssayCode=[ElementAnalyzer].AssayCode
				LEFT JOIN [LightWaveMeter] ON [CoalInfo].AssayCode=[LightWaveMeter].AssayCode
				LEFT JOIN [SulfurDetector] ON [CoalInfo].AssayCode=[SulfurDetector].AssayCode
				LEFT JOIN [WorkPointInstrument] ON [CoalInfo].AssayCode=[WorkPointInstrument].AssayCode				
			EXEC [dbo].Track @Token,'SELECT','SearchCoal', 'SUCCESS'
		END
		ELSE IF @Condition = 'StaffAndDate'
		BEGIN
			SELECT 
				[CoalLotNum],[CoalInfo].[AssayCode],[CoalInfo].[AssayDate],[SampleDate],[AssayType],[CoalInfo].[AssayStaff],[SampleStaff],[StageName],[WorksName]
				,[Qb_ad],[Qgr_d],[Qgr_a],[Qnet_ar]
				,[AshFusionT1],[AshFusionT2],[AshFusionT3],[AshFusionT4]
				,[Had]
				,[Mar]
				,[St_ad],[St_d]
				,[Vd],[Vad],[Var],[Vdaf],[Mad],[Aad],[Aar]
			FROM
				[CoalInfo]
				LEFT JOIN [CaloriMeter] ON 
						  [CoalInfo].AssayStaff = @AssayStaff
						  AND [CoalInfo].AssayDate<=@EndDate 
						  AND [CoalInfo].AssayDate >= @BeginDate 
						  AND [CoalInfo].AssayCode=[CaloriMeter].AssayCode
				LEFT JOIN [AshFusionPoint] ON [CoalInfo].AssayCode=[AshFusionPoint].AssayCode
				LEFT JOIN [ElementAnalyzer] ON [CoalInfo].AssayCode=[ElementAnalyzer].AssayCode
				LEFT JOIN [LightWaveMeter] ON [CoalInfo].AssayCode=[LightWaveMeter].AssayCode
				LEFT JOIN [SulfurDetector] ON [CoalInfo].AssayCode=[SulfurDetector].AssayCode
				LEFT JOIN [WorkPointInstrument] ON [CoalInfo].AssayCode=[WorkPointInstrument].AssayCode
			EXEC [dbo].Track @Token,'SELECT','SearchCoal', 'SUCCESS'
		END
		ELSE
		BEGIN
			EXEC [dbo].Track @Token,'SELECT','SearchCoal', 'ERROR Bad Query'
			
		END		
	END
	ELSE
	BEGIN
		SELECT 'ERROR Permission Denied' AS SELECTALLRESULT
		EXEC [dbo].Track @Token,'SELECT','SearchCoal', 'ERROR Permission Denied'
	END	
END
GO