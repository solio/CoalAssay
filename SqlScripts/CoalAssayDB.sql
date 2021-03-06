USE [CoalAssay]
GO
/****** Object:  Table [dbo].[Device]    Script Date: 11/04/2013 18:25:06 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Device](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[DeviceName] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_Device] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[CoalInfo]    Script Date: 11/04/2013 18:25:06 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[CoalInfo](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[CoalLotNum] [nvarchar](20) NOT NULL,
	[AssayCode] [nvarchar](20) NOT NULL,
	[AssayDate] [datetime] NOT NULL,
	[SampleDate] [datetime] NOT NULL,
	[AssayType] [tinyint] NOT NULL,
	[AssayStaff] [nvarchar](20) NOT NULL,
	[SampleStaff] [nvarchar](20) NULL,
	[StageName] [nchar](10) NULL,
	[WorksName] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_CoalInfo] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'接受批号' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'CoalInfo', @level2type=N'COLUMN',@level2name=N'CoalLotNum'
GO
/****** Object:  Table [dbo].[Staff]    Script Date: 11/04/2013 18:25:06 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Staff](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[StaffName] [nvarchar](10) NOT NULL,
	[StaffSex] [bit] NOT NULL,
	[StaffBirthday] [int] NOT NULL,
	[Position] [nvarchar](50) NOT NULL,
	[Password] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_Staff] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'0女 1男' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Staff', @level2type=N'COLUMN',@level2name=N'StaffSex'
GO
/****** Object:  Table [dbo].[WorkpointInstrument]    Script Date: 11/04/2013 18:25:06 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[WorkpointInstrument](
	[AssayID] [int] NOT NULL,
	[DeviceID] [int] NOT NULL,
	[Vd] [numeric](8, 2) NOT NULL,
	[Vad] [numeric](8, 2) NOT NULL,
	[Var] [numeric](8, 2) NOT NULL,
	[Vdaf] [numeric](8, 2) NOT NULL,
	[Mar] [numeric](8, 2) NOT NULL,
	[Mad] [numeric](8, 2) NOT NULL,
	[Aad] [numeric](8, 2) NOT NULL,
	[Aar] [numeric](8, 2) NOT NULL,
 CONSTRAINT [PK_WorkpointInstrument] PRIMARY KEY CLUSTERED 
(
	[AssayID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'工分仪测量信息表' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'WorkpointInstrument'
GO
/****** Object:  Table [dbo].[SulfurDetector]    Script Date: 11/04/2013 18:25:06 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[SulfurDetector](
	[AssayID] [int] NOT NULL,
	[DeviceID] [int] NOT NULL,
	[St_ad] [numeric](8, 2) NOT NULL,
	[St_d] [numeric](8, 2) NOT NULL,
 CONSTRAINT [PK_SulfurDetector] PRIMARY KEY CLUSTERED 
(
	[AssayID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'煤样ID，外键约束' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SulfurDetector', @level2type=N'COLUMN',@level2name=N'AssayID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'测硫仪测量信息表' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SulfurDetector'
GO
/****** Object:  Table [dbo].[LightWaveMeter]    Script Date: 11/04/2013 18:25:06 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LightWaveMeter](
	[AssayID] [int] NOT NULL,
	[DeviceID] [int] NOT NULL,
	[Mar] [numeric](8, 2) NOT NULL,
	[Mad] [numeric](8, 2) NOT NULL,
 CONSTRAINT [PK_LightWaveMeter] PRIMARY KEY CLUSTERED 
(
	[AssayID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'光波仪测量信息表' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'LightWaveMeter'
GO
/****** Object:  Table [dbo].[ElementAnalyzer]    Script Date: 11/04/2013 18:25:06 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ElementAnalyzer](
	[AssayID] [int] NOT NULL,
	[DeviceID] [int] NOT NULL,
	[Had] [numeric](8, 2) NOT NULL,
 CONSTRAINT [PK_ElementAnalyzer] PRIMARY KEY CLUSTERED 
(
	[AssayID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'元素分析仪测量信息表' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ElementAnalyzer'
GO
/****** Object:  Table [dbo].[Calorimeter]    Script Date: 11/04/2013 18:25:06 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Calorimeter](
	[AssayID] [int] NOT NULL,
	[DeviceID] [int] NOT NULL,
	[Qb_ad] [numeric](8, 3) NOT NULL,
	[Qgr_d] [numeric](8, 3) NOT NULL,
	[Qgr_a] [numeric](8, 3) NOT NULL,
	[Qnet_ar] [numeric](8, 3) NOT NULL,
 CONSTRAINT [PK_HeatDetector] PRIMARY KEY CLUSTERED 
(
	[AssayID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'量热仪测量信息表' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Calorimeter'
GO
/****** Object:  Table [dbo].[AshFusionPoint ]    Script Date: 11/04/2013 18:25:06 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AshFusionPoint ](
	[AssayID] [int] NOT NULL,
	[DeviceID] [int] NOT NULL,
	[AshFusionT1] [numeric](8, 2) NOT NULL,
	[AshFusionT2] [numeric](8, 2) NOT NULL,
	[AshFusionT3] [numeric](8, 2) NOT NULL,
	[AshFusionT4] [numeric](8, 2) NOT NULL,
 CONSTRAINT [PK_AshMeltingPoint ] PRIMARY KEY CLUSTERED 
(
	[AssayID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'智能灰熔点分析测量信息表' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AshFusionPoint '
GO
/****** Object:  ForeignKey [FK_WorkpointInstrument_CoalInfo]    Script Date: 11/04/2013 18:25:06 ******/
ALTER TABLE [dbo].[WorkpointInstrument]  WITH CHECK ADD  CONSTRAINT [FK_WorkpointInstrument_CoalInfo] FOREIGN KEY([AssayID])
REFERENCES [dbo].[CoalInfo] ([ID])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[WorkpointInstrument] CHECK CONSTRAINT [FK_WorkpointInstrument_CoalInfo]
GO
/****** Object:  ForeignKey [FK_WorkpointInstrument_Device]    Script Date: 11/04/2013 18:25:06 ******/
ALTER TABLE [dbo].[WorkpointInstrument]  WITH CHECK ADD  CONSTRAINT [FK_WorkpointInstrument_Device] FOREIGN KEY([AssayID])
REFERENCES [dbo].[Device] ([ID])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[WorkpointInstrument] CHECK CONSTRAINT [FK_WorkpointInstrument_Device]
GO
/****** Object:  ForeignKey [FK_SulfurDetector_CoalInfo]    Script Date: 11/04/2013 18:25:06 ******/
ALTER TABLE [dbo].[SulfurDetector]  WITH CHECK ADD  CONSTRAINT [FK_SulfurDetector_CoalInfo] FOREIGN KEY([AssayID])
REFERENCES [dbo].[CoalInfo] ([ID])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[SulfurDetector] CHECK CONSTRAINT [FK_SulfurDetector_CoalInfo]
GO
/****** Object:  ForeignKey [FK_SulfurDetector_Device]    Script Date: 11/04/2013 18:25:06 ******/
ALTER TABLE [dbo].[SulfurDetector]  WITH CHECK ADD  CONSTRAINT [FK_SulfurDetector_Device] FOREIGN KEY([DeviceID])
REFERENCES [dbo].[Device] ([ID])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[SulfurDetector] CHECK CONSTRAINT [FK_SulfurDetector_Device]
GO
/****** Object:  ForeignKey [FK_LightWaveMeter_Device]    Script Date: 11/04/2013 18:25:06 ******/
ALTER TABLE [dbo].[LightWaveMeter]  WITH CHECK ADD  CONSTRAINT [FK_LightWaveMeter_Device] FOREIGN KEY([AssayID])
REFERENCES [dbo].[Device] ([ID])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[LightWaveMeter] CHECK CONSTRAINT [FK_LightWaveMeter_Device]
GO
/****** Object:  ForeignKey [FK_LightWaveMeter_LightWaveMeter]    Script Date: 11/04/2013 18:25:06 ******/
ALTER TABLE [dbo].[LightWaveMeter]  WITH CHECK ADD  CONSTRAINT [FK_LightWaveMeter_LightWaveMeter] FOREIGN KEY([AssayID])
REFERENCES [dbo].[CoalInfo] ([ID])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[LightWaveMeter] CHECK CONSTRAINT [FK_LightWaveMeter_LightWaveMeter]
GO
/****** Object:  ForeignKey [FK_ElementAnalyzer_CoalInfo]    Script Date: 11/04/2013 18:25:06 ******/
ALTER TABLE [dbo].[ElementAnalyzer]  WITH CHECK ADD  CONSTRAINT [FK_ElementAnalyzer_CoalInfo] FOREIGN KEY([AssayID])
REFERENCES [dbo].[CoalInfo] ([ID])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[ElementAnalyzer] CHECK CONSTRAINT [FK_ElementAnalyzer_CoalInfo]
GO
/****** Object:  ForeignKey [FK_ElementAnalyzer_Device]    Script Date: 11/04/2013 18:25:06 ******/
ALTER TABLE [dbo].[ElementAnalyzer]  WITH CHECK ADD  CONSTRAINT [FK_ElementAnalyzer_Device] FOREIGN KEY([AssayID])
REFERENCES [dbo].[Device] ([ID])
GO
ALTER TABLE [dbo].[ElementAnalyzer] CHECK CONSTRAINT [FK_ElementAnalyzer_Device]
GO
/****** Object:  ForeignKey [FK_Calorimeter_CoalInfo]    Script Date: 11/04/2013 18:25:06 ******/
ALTER TABLE [dbo].[Calorimeter]  WITH CHECK ADD  CONSTRAINT [FK_Calorimeter_CoalInfo] FOREIGN KEY([AssayID])
REFERENCES [dbo].[CoalInfo] ([ID])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[Calorimeter] CHECK CONSTRAINT [FK_Calorimeter_CoalInfo]
GO
/****** Object:  ForeignKey [FK_Calorimeter_Device]    Script Date: 11/04/2013 18:25:06 ******/
ALTER TABLE [dbo].[Calorimeter]  WITH CHECK ADD  CONSTRAINT [FK_Calorimeter_Device] FOREIGN KEY([DeviceID])
REFERENCES [dbo].[Device] ([ID])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[Calorimeter] CHECK CONSTRAINT [FK_Calorimeter_Device]
GO
/****** Object:  ForeignKey [FK_AshMeltingPoint _CoalInfo]    Script Date: 11/04/2013 18:25:06 ******/
ALTER TABLE [dbo].[AshFusionPoint ]  WITH CHECK ADD  CONSTRAINT [FK_AshMeltingPoint _CoalInfo] FOREIGN KEY([AssayID])
REFERENCES [dbo].[CoalInfo] ([ID])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[AshFusionPoint ] CHECK CONSTRAINT [FK_AshMeltingPoint _CoalInfo]
GO
/****** Object:  ForeignKey [FK_AshMeltingPoint _Device]    Script Date: 11/04/2013 18:25:06 ******/
ALTER TABLE [dbo].[AshFusionPoint ]  WITH CHECK ADD  CONSTRAINT [FK_AshMeltingPoint _Device] FOREIGN KEY([AssayID])
REFERENCES [dbo].[Device] ([ID])
GO
ALTER TABLE [dbo].[AshFusionPoint ] CHECK CONSTRAINT [FK_AshMeltingPoint _Device]
GO
