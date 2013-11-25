USE CoalAssay

DELETE FROM [CoalInfo] WHERE [ID] IN (SELECT MAX([ID]) FROM [CoalInfo])
DELETE FROM [CaloriMeter] WHERE [ID] IN (SELECT MAX([ID]) FROM [CaloriMeter])
DELETE FROM [AshFusionPoint] WHERE [ID] IN (SELECT MAX([ID]) FROM [AshFusionPoint])
DELETE FROM [ElementAnalyzer] WHERE [ID] IN (SELECT MAX([ID]) FROM [ElementAnalyzer])
DELETE FROM [LightWaveMeter] WHERE [ID] IN (SELECT MAX([ID]) FROM [LightWaveMeter])
DELETE FROM [SulfurDetector] WHERE [ID] IN (SELECT MAX([ID]) FROM [SulfurDetector])
DELETE FROM [WorkPointInstrument] WHERE [ID] IN (SELECT MAX([ID]) FROM [WorkPointInstrument])