<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="17008000">
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">false</Property>
	<Property Name="SMProvider.SMVersion" Type="Int">201310</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="IOScan.Faults" Type="Str"></Property>
		<Property Name="IOScan.NetVarPeriod" Type="UInt">100</Property>
		<Property Name="IOScan.NetWatchdogEnabled" Type="Bool">false</Property>
		<Property Name="IOScan.Period" Type="UInt">10000</Property>
		<Property Name="IOScan.PowerupMode" Type="UInt">0</Property>
		<Property Name="IOScan.Priority" Type="UInt">9</Property>
		<Property Name="IOScan.ReportModeConflict" Type="Bool">true</Property>
		<Property Name="IOScan.StartEngineOnDeploy" Type="Bool">false</Property>
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Support VIs" Type="Folder">
			<Property Name="NI.SortType" Type="Int">3</Property>
			<Item Name="Msg Notifiers" Type="Folder">
				<Item Name="Close Notifiers.vi" Type="VI" URL="../support/Notifiers/Close Notifiers.vi"/>
				<Item Name="Create Notifiers.vi" Type="VI" URL="../support/Notifiers/Create Notifiers.vi"/>
				<Item Name="Notifiers.ctl" Type="VI" URL="../support/Notifiers/Notifiers.ctl"/>
			</Item>
			<Item Name="Data Notifiers" Type="Folder">
				<Item Name="data_Close Notifiers.vi" Type="VI" URL="../support/data_notifiers/data_Close Notifiers.vi"/>
				<Item Name="data_Create Notifiers.vi" Type="VI" URL="../support/data_notifiers/data_Create Notifiers.vi"/>
				<Item Name="data_Notifiers.ctl" Type="VI" URL="../support/data_notifiers/data_Notifiers.ctl"/>
			</Item>
			<Item Name="Data Queue" Type="Folder">
				<Item Name="all_data_queue.ctl" Type="VI" URL="../support/data_queue/all_data_queue.ctl"/>
				<Item Name="create_all_data_queue.vi" Type="VI" URL="../support/data_queue/create_all_data_queue.vi"/>
				<Item Name="close_all_data_queue.vi" Type="VI" URL="../support/data_queue/close_all_data_queue.vi"/>
			</Item>
			<Item Name="Message Queue.lvlib" Type="Library" URL="../support/Message Queue/Message Queue.lvlib"/>
			<Item Name="User Event - Stop.lvlib" Type="Library" URL="../support/User Event - Stop/User Event - Stop.lvlib"/>
			<Item Name="Check Loop Error.vi" Type="VI" URL="../support/Check Loop Error.vi"/>
			<Item Name="Error Handler - Event Handling Loop.vi" Type="VI" URL="../support/Error Handler - Event Handling Loop.vi"/>
			<Item Name="Error Handler - Message Handling Loop.vi" Type="VI" URL="../support/Error Handler - Message Handling Loop.vi"/>
			<Item Name="my_global.vi" Type="VI" URL="../support/my_global.vi"/>
			<Item Name="measurement_loop_template.vi" Type="VI" URL="../support/measurement_loop_template.vi"/>
			<Item Name="measurement_state.ctl" Type="VI" URL="../support/measurement_state.ctl"/>
			<Item Name="relativ_path_to_absolute_path.vi" Type="VI" URL="../support/relativ_path_to_absolute_path.vi"/>
		</Item>
		<Item Name="Type Definitions" Type="Folder">
			<Item Name="UI Data.ctl" Type="VI" URL="../controls/UI Data.ctl"/>
		</Item>
		<Item Name="Stub" Type="Folder">
			<Item Name="2d_array.vi" Type="VI" URL="../stub/2d_array.vi"/>
			<Item Name="configuration_file.vi" Type="VI" URL="../stub/configuration_file.vi"/>
			<Item Name="create_virtual_channel.vi" Type="VI" URL="../stub/create_virtual_channel.vi"/>
			<Item Name="data_decimate.vi" Type="VI" URL="../stub/data_decimate.vi"/>
			<Item Name="os_name.vi" Type="VI" URL="../stub/os_name.vi"/>
		</Item>
		<Item Name="Read Analog Worker" Type="Folder">
			<Item Name="read_analog_worker_loop.vi" Type="VI" URL="../read_analog_worker/read_analog_worker_loop.vi"/>
			<Item Name="test_read_analog_worker.vi" Type="VI" URL="../read_analog_worker/test_read_analog_worker.vi"/>
		</Item>
		<Item Name="Read Digital Worker" Type="Folder">
			<Item Name="read_digital_worker_loop.vi" Type="VI" URL="../read_digital_worker/read_digital_worker_loop.vi"/>
			<Item Name="test_read_digital_worker.vi" Type="VI" URL="../read_digital_worker/test_read_digital_worker.vi"/>
		</Item>
		<Item Name="DataFrame.lvclass" Type="LVClass" URL="../dataframe/DataFrame.lvclass"/>
		<Item Name="logger.lvlib" Type="Library" URL="../logger/logger.lvlib"/>
		<Item Name="request_processor.lvlib" Type="Library" URL="../request_processor/request_processor.lvlib"/>
		<Item Name="tcp_server.lvlib" Type="Library" URL="../tcp_server/tcp_server.lvlib"/>
		<Item Name="Hardware.lvclass" Type="LVClass" URL="../hardware/Hardware.lvclass"/>
		<Item Name="Measurement.lvclass" Type="LVClass" URL="../measurement/Measurement.lvclass"/>
		<Item Name="main.vi" Type="VI" URL="../main.vi"/>
		<Item Name="AO_Ni_Hardware.lvclass" Type="LVClass" URL="../ao_ni_hardware/AO_Ni_Hardware.lvclass"/>
		<Item Name="DI_Ni_Hardware.lvclass" Type="LVClass" URL="../di_ni_hardware/DI_Ni_Hardware.lvclass"/>
		<Item Name="DO_Ni_Hardware.lvclass" Type="LVClass" URL="../do_ni_hardware/DO_Ni_Hardware.lvclass"/>
		<Item Name="AI_Ni_Hardware.lvclass" Type="LVClass" URL="../ai_ni_hardware/AI_Ni_Hardware.lvclass"/>
		<Item Name="DigitalSimHardware.lvclass" Type="LVClass" URL="../digital_sim_hardware/DigitalSimHardware.lvclass"/>
		<Item Name="AnalogSimHardware.lvclass" Type="LVClass" URL="../analog_sim_hardware/AnalogSimHardware.lvclass"/>
		<Item Name="MeasurementDatalvclass.lvclass" Type="LVClass" URL="../measurement_data/MeasurementDatalvclass.lvclass"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="Application Directory.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Application Directory.vi"/>
				<Item Name="NI_LVConfig.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/config.llb/NI_LVConfig.lvlib"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
				<Item Name="NI_PackedLibraryUtility.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/LVLibp/NI_PackedLibraryUtility.lvlib"/>
				<Item Name="8.6CompatibleGlobalVar.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/config.llb/8.6CompatibleGlobalVar.vi"/>
				<Item Name="DAQmx Read.vi" Type="VI" URL="/&lt;vilib&gt;/DAQmx/read.llb/DAQmx Read.vi"/>
				<Item Name="DAQmx Fill In Error Info.vi" Type="VI" URL="/&lt;vilib&gt;/DAQmx/miscellaneous.llb/DAQmx Fill In Error Info.vi"/>
				<Item Name="DAQmx Read (Analog 2D I16 NChan NSamp).vi" Type="VI" URL="/&lt;vilib&gt;/DAQmx/read.llb/DAQmx Read (Analog 2D I16 NChan NSamp).vi"/>
				<Item Name="DAQmx Create Virtual Channel.vi" Type="VI" URL="/&lt;vilib&gt;/DAQmx/create/channels.llb/DAQmx Create Virtual Channel.vi"/>
				<Item Name="DAQmx Create Channel (AI-Voltage-Basic).vi" Type="VI" URL="/&lt;vilib&gt;/DAQmx/create/channels.llb/DAQmx Create Channel (AI-Voltage-Basic).vi"/>
				<Item Name="DAQmx Create Channel (AI-Temperature-Thermocouple).vi" Type="VI" URL="/&lt;vilib&gt;/DAQmx/create/channels.llb/DAQmx Create Channel (AI-Temperature-Thermocouple).vi"/>
				<Item Name="DAQmx Start Task.vi" Type="VI" URL="/&lt;vilib&gt;/DAQmx/configure/task.llb/DAQmx Start Task.vi"/>
				<Item Name="Get LV Class Default Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/LVClass/Get LV Class Default Value.vi"/>
			</Item>
			<Item Name="nilvaiu.dll" Type="Document" URL="nilvaiu.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="MeasurementDatalvclass.lvclass" Type="LVClass" URL="../measurement_result/MeasurementDatalvclass.lvclass"/>
			<Item Name="get_time_stamp.vi" Type="VI" URL="../measurement_result/get_time_stamp.vi"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="server" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{51D186D8-2FD9-4F4B-8F36-40D68E57FFBC}</Property>
				<Property Name="App_INI_GUID" Type="Str">{F8BAE070-8383-465E-800B-3DF9D752A65B}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{96FCFFEE-92FF-41D7-8A5C-2E1B7D4F08B1}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">server</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../build/NI_AB_PROJECTNAME</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{9236DFC5-A1BE-45C5-93F4-A12737594CB8}</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Destination[0].destName" Type="Str">server.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../build/NI_AB_PROJECTNAME/Server.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../build/NI_AB_PROJECTNAME/data</Property>
				<Property Name="SourceCount" Type="Int">3</Property>
				<Property Name="Source[0].itemID" Type="Str">{75986B3C-667E-452D-8523-43660F32521F}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref"></Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/Support VIs/my_global.vi</Property>
				<Property Name="Source[2].type" Type="Str">VI</Property>
				<Property Name="TgtF_fileDescription" Type="Str">server</Property>
				<Property Name="TgtF_internalName" Type="Str">server</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2012 </Property>
				<Property Name="TgtF_productName" Type="Str">server</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{8D31CF1E-BFEE-4FAB-AC90-991853A95B09}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">server.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
