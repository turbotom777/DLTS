/*************************************************************************
*
*    NI-DAQ Windows - Function Prototypes
*    Copyright    (C) National Instruments 1995.
*
*************************************************************************/


typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef long i32;
typedef unsigned long u32;
typedef float f32;
typedef double f64;

#ifndef FAR
#define __locallydefinedFAR
#define FAR
#endif

#ifdef __cplusplus
extern "C" { 
#endif

extern i16 WINAPI A2000_Calibrate (
	i16        slot,
	i16        saveNewValues,
	i16        calMethod,
	i16        channel,
	f64        extRefVoltage);
extern i16 WINAPI A2000_Config (
	i16        slot,
	i16        sampClkSrc,
	i16        sampClkDrv,
	i16        dither);
extern i16 WINAPI A2150_Calibrate (
	i16        slot,
	i16        ref0,
	i16        ref1);
extern i16 WINAPI AI_Check (
	i16        slot,
	i16        FAR * status,
	i16        FAR * value);
extern i16 WINAPI AI_Clear (
	i16        slot);
extern i16 WINAPI AI_Configure (
	i16        slot,
	i16        chan,
	i16        inputMode,
	i16        inputRange,
	i16        polarity,
	i16        driveAIS);
extern i16 WINAPI AI_Mux_Config (
	i16        slot,
	i16        numMuxBrds);
extern i16 WINAPI AI_Read (
	i16        slot,
	i16        chan,
	i16        gain,
	i16        FAR * value);
extern i16 WINAPI AI_Setup (
	i16        slot,
	i16        chan,
	i16        gain);
extern i16 WINAPI AI_VRead (
	i16        slot,
	i16        chan,
	i16        gain,
	f64        FAR * volts);
extern i16 WINAPI AI_VScale (
	i16        slot,
	i16        chan,
	i16        gain,
	f64        gainAdjust,
	f64        offset,
	i16        reading,
	f64        FAR * voltage);
extern i16 WINAPI Align_DMA_Buffer (
	i16        slot,
	i16        resource,
	i16        FAR * buffer,
	u32        cnt,
	u32        bufSize,
	u32        FAR * alignIndex);
extern i16 WINAPI AO_Calibrate (
	i16        board,
	i16        operation,
	i16        EEPROMloc);
extern i16 WINAPI AO_Configure (
	i16        slot,
	i16        chan,
	i16        outputPolarity,
	i16        IntOrExtRef,
	f64        refVoltage,
	i16        updateMode);
extern i16 WINAPI AO_Change_Parameter (
	i16        slot,
	i16        channel,
	u32        paramID,
	u32        paramValue);
extern i16 WINAPI AO_Update (
	i16        slot);
extern i16 WINAPI AO_VWrite (
	i16        slot,
	i16        chan,
	f64        voltage);
extern i16 WINAPI AO_Write (
	i16        slot,
	i16        chan,
	i16        value);
extern i16 WINAPI Calibrate_E_Series (
	i16        deviceNumber,
	u32        calOp,
	u32        setOfCalConst,
	f64        calRefVolts);
extern i16 WINAPI Config_Alarm_Deadband (
	i16        slot,
	i16        mode,
	i8         FAR * chanStr,
	f64        trigLvl,
	f64        deadbandWidth,
	HWND       handle,
	i16        alarmOnMsg,
	i16        alarmOffMsg,
	u32        callbackAddr);
extern i16 WINAPI Config_ATrig_Event_Message (
	i16        slot,
	i16        mode,
	i8         FAR * chanStr,
	f64        trigLvl,
	f64        winSize,
	i16        trigSlope,
	u32        skipCnt,
	u32        preTrigScans,
	u32        postTrigScans,
	HWND       handle,
	i16        msg,
	u32        callBackAddr);
extern i16 WINAPI Config_DAQ_Event_Message (
	i16        slot,
	i16        mode,
	i8         FAR * chanStr,
	i16        DAQEvent,
	i32        trigVal0,
	i32        trigVal1,
	u32        skipCnt,
	u32        preTrigScans,
	u32        postTrigScans,
	HWND       handle,
	i16        msg,
	u32        callBackAddr);
extern i16 WINAPI Configure_HW_Analog_Trigger (
	i16        deviceNumber,
	u32        onOrOff,
	i32        lowValue,
	i32        highValue,
	u32        mode,
	u32        trigSource);
extern i16 WINAPI CTR_Config (
	i16        slot,
	i16        ctr,
	i16        edgeMode,
	i16        gateMode,
	i16        outType,
	i16        outPolarity);
extern i16 WINAPI CTR_EvCount (
	i16        slot,
	i16        ctr,
	i16        timebase,
	i16        cont);
extern i16 WINAPI CTR_EvRead (
	i16        slot,
	i16        ctr,
	i16        FAR * overflow,
	u16        FAR * counts);
extern i16 WINAPI CTR_FOUT_Config (
	i16        slot,
	i16        FOUT,
	i16        mode,
	i16        timebase,
	i16        division);
extern i16 WINAPI CTR_Period (
	i16        slot,
	i16        ctr,
	i16        timebase);
extern i16 WINAPI CTR_Pulse (
	i16        slot,
	i16        ctr,
	i16        timebase,
	u16        delay,
	u16        pulseWidth);
extern i16 WINAPI CTR_Rate (
	f64        freq,
	f64        duty,
	i16        FAR * timebase,
	u16        FAR * period1,
	u16        FAR * period2);
extern i16 WINAPI CTR_Reset (
	i16        slot,
	i16        ctr,
	i16        outState);
extern i16 WINAPI CTR_Restart (
	i16        slot,
	i16        ctr);
extern i16 WINAPI CTR_Simul_Op (
	i16        slot,
	i16        numCtrs,
	i16        FAR * ctrList,
	i16        mode);
extern i16 WINAPI CTR_Square (
	i16        slot,
	i16        ctr,
	i16        timebase,
	u16        period1,
	u16        period2);
extern i16 WINAPI CTR_State (
	i16        slot,
	i16        ctr,
	i16        FAR * outState);
extern i16 WINAPI CTR_Stop (
	i16        slot,
	i16        ctr);
extern i16 WINAPI DAQ_Check (
	i16        slot,
	i16        FAR * status,
	u32        FAR * retrieved);
extern i16 WINAPI DAQ_Clear (
	i16        slot);
extern i16 WINAPI DAQ_Config (
	i16        slot,
	i16        startTrig,
	i16        extConv);
extern i16 WINAPI DAQ_DB_Config (
	i16        slot,
	i16        dbMode);
extern i16 WINAPI DAQ_DB_HalfReady (
	i16        slot,
	i16        FAR * halfReady,
	i16        FAR * status);
extern i16 WINAPI DAQ_DB_StrTransfer (
	i16        slot,
	i8         FAR * buffer,
	u32        FAR * ptsTfr,
	i16        FAR * status);
extern i16 WINAPI DAQ_DB_Transfer (
	i16        slot,
	i16        FAR * hbuffer,
	u32        FAR * ptsTfr,
	i16        FAR * status);
extern i16 WINAPI DAQ_Monitor (
	i16        slot,
	i16        chan,
	i16        seq,
	u32        monitorCnt,
	i16        FAR * monitorBuf,
	u32        FAR * newestIndex,
	i16        FAR * status);
extern i16 WINAPI DAQ_Op (
	i16        slot,
	i16        chan,
	i16        gain,
	i16        FAR * buffer,
	u32        cnt,
	f64        sampleRate);
extern i16 WINAPI DAQ_Rate (
	f64        rate,
	i16        units,
	i16        FAR * timebase,
	u16        FAR * sampleInt);
extern i16 WINAPI DAQ_Start (
	i16        slot,
	i16        chan,
	i16        gain,
	i16        FAR * buffer,
	u32        cnt,
	i16        timebase,
	u16        sampInt);
extern i16 WINAPI DAQ_StopTrigger_Config (
	i16        slot,
	i16        preTrig,
	u32        preTrigCnt);
extern i16 WINAPI DAQ_to_Disk (
	i16        slot,
	i16        chan,
	i16        gain,
	i8         FAR * fileName,
	u32        cnt,
	f64        sampleRate,
	i16        concat);
extern i16 WINAPI DAQ_VScale (
	i16        slot,
	i16        chan,
	i16        gain,
	f64        gainAdjust,
	f64        offset,
	u32        cnt,
	i16        FAR * binArray,
	f64        FAR * voltArray);
extern i16 WINAPI DIG_Block_Check (
	i16        slot,
	i16        grp,
	u32        FAR * remaining);
extern i16 WINAPI DIG_Block_Clear (
	i16        slot,
	i16        grp);
extern i16 WINAPI DIG_Block_In (
	i16        slot,
	i16        grp,
	i16        FAR * buffer,
	u32        cnt);
extern i16 WINAPI DIG_Block_Out (
	i16        slot,
	i16        grp,
	i16        FAR * buffer,
	u32        cnt);
extern i16 WINAPI DIG_Block_PG_Config (
	i16        slot,
	i16        grp,
	i16        PGmode,
	i16        reqSource,
	i16        timebase,
	u16        interval,
	i16        externalGate);
extern i16 WINAPI DIG_DB_Config (
	i16        slot,
	i16        grp,
	i16        DBMode,
	i16        oldDataStop,
	i16        partialTransfer);
extern i16 WINAPI DIG_DB_HalfReady (
	i16        slot,
	i16        grp,
	i16        FAR * halfReady);
extern i16 WINAPI DIG_DB_StrTransfer (
	i16        slot,
	i16        grp,
	i8         FAR * halfBuffer,
	u32        ptsTfr);
extern i16 WINAPI DIG_DB_Transfer (
	i16        slot,
	i16        grp,
	i16        FAR * halfBuffer,
	u32        ptsTfr);
extern i16 WINAPI DIG_Grp_Config (
	i16        slot,
	i16        grp,
	i16        grpsize,
	i16        port,
	i16        direction);
extern i16 WINAPI DIG_Grp_Mode (
	i16        slot,
	i16        grp,
	i16        sigType,
	i16        edge,
	i16        reqpol,
	i16        ackpol,
	i16        settleTime);
extern i16 WINAPI DIG_Grp_Status (
	i16        slot,
	i16        grp,
	i16        FAR * status);
extern i16 WINAPI DIG_In_Grp (
	i16        slot,
	i16        grp,
	i16        FAR * grp_pat);
extern i16 WINAPI DIG_In_Line (
	i16        slot,
	i16        port,
	i16        linenum,
	i16        FAR * status);
extern i16 WINAPI DIG_In_Port (
	i16        slot,
	i16        port,
	i16        FAR * pattern);
extern i16 WINAPI DIG_Line_Config (
	i16        slot,
	i16        port,
	i16        linenum,
	i16        direction);
extern i16 WINAPI DIG_Out_Grp (
	i16        slot,
	i16        grp,
	i16        grp_pat);
extern i16 WINAPI DIG_Out_Line (
	i16        slot,
	i16        port,
	i16        linenum,
	i16        status);
extern i16 WINAPI DIG_Out_Port (
	i16        slot,
	i16        port,
	i16        pattern);
extern i16 WINAPI DIG_Prt_Config (
	i16        slot,
	i16        port,
	i16        latch_mode,
	i16        direction);
extern i16 WINAPI DIG_Prt_Status (
	i16        slot,
	i16        port,
	i16        FAR * status);
extern i16 WINAPI DIG_SCAN_Setup (
	i16        slot,
	i16        grp,
	i16        numPorts,
	i16        FAR * portList,
	i16        direction);
extern i16 WINAPI DSP2200_Calibrate (
	i16        slot,
	i16        mode,
	i16        ADCref);
extern i16 WINAPI DSP2200_Config (
	i16        slot,
	i16        aitranslate,
	i16        aotranslate,
	i16        demux);
extern i16 WINAPI Get_DAQ_Device_Info (
	i16        deviceNumber,
	u32        infoType,
	u32        FAR * infoVal);
extern i16 WINAPI Get_DAQ_Event (
	u32        timeOut,
	i16        FAR * handle,
	i16        FAR * msg,
	i16        FAR * wParam,
	i32        FAR * lParam);
extern i16 WINAPI Get_NI_DAQ_Version (
	u32        FAR * version);
extern i16 WINAPI GPCTR_Config_Buffer (
	i16        deviceNumber,
	u32        gpCounterNumber,
	u32        reserved,
	u32        numPoints,
	u32        FAR * buffer);
extern i16 WINAPI GPCTR_Control (
	i16        deviceNumber,
	u32        gpCounterNumber,
	u32        action);
extern i16 WINAPI GPCTR_Set_Application (
	i16        deviceNumber,
	u32        gpCounterNumber,
	u32        application);
extern i16 WINAPI GPCTR_Watch (
	i16        deviceNumber,
	u32        gpCounterNumber,
	u32        watchID,
	u32        FAR * watchValue);
extern i16 WINAPI ICTR_Read (
	i16        slot,
	i16        counter,
	u16        FAR * cnt);
extern i16 WINAPI ICTR_Reset (
	i16        slot,
	i16        counter,
	i16        state);
extern i16 WINAPI ICTR_Setup (
	i16        slot,
	i16        counter,
	i16        mode,
	u16        cnt,
	i16        binBCD);
extern i16 WINAPI Init_DA_Brds (
	i16        slot,
	i16        FAR * brdCode);
extern i16 WINAPI Lab_ISCAN_Check (
	i16        slot,
	i16        FAR * status,
	u32        FAR * retrieved,
	i16        FAR * finalScanOrder);
extern i16 WINAPI Lab_ISCAN_Op (
	i16        slot,
	i16        numChans,
	i16        gain,
	i16        FAR * buffer,
	u32        cnt,
	f64        sampleRate,
	f64        scanRate,
	i16        FAR * finalScanOrder);
extern i16 WINAPI Lab_ISCAN_Start (
	i16        slot,
	i16        numChans,
	i16        gain,
	i16        FAR * buffer,
	u32        cnt,
	i16        timebase,
	u16        sampleInt,
	u16        scanInt);
extern i16 WINAPI Lab_ISCAN_to_Disk (
	i16        slot,
	i16        numChans,
	i16        gain,
	i8         FAR * fileName,
	u32        cnt,
	f64        sampleRate,
	f64        scanRate,
	i16        concat);
extern i16 WINAPI LPM16_Calibrate (
	i16        slot);
extern i16 WINAPI MAI_Arm (
	i16        slot,
	i16        onOff);
extern i16 WINAPI MAI_Clear (
	i16        slot);
extern i16 WINAPI MAI_Coupling (
	i16        slot,
	i16        numChans,
	i16        FAR * coupling);
extern i16 WINAPI MAI_Read (
	i16        slot,
	i16        FAR * reading);
extern i16 WINAPI MAI_Scale (
	i16        slot,
	u32        numScans,
	i16        FAR * values,
	f64        FAR * volts);
extern i16 WINAPI MAI_Setup (
	i16        slot,
	i16        numChans,
	i16        FAR * chanList,
	i16        FAR * gainList,
	u16        muxInterval,
	i16        timebase,
	i16        muxMode);
extern i16 WINAPI Master_Slave_Config (
	i16        slot,
	i16        numSlaves,
	i16        FAR * saveList);
extern i16 WINAPI MDAQ_Check (
	i16        slot,
	i16        fullCheck,
	i16        FAR * acqDone,
	u32        FAR * framesDone,
	u32        FAR * scansDone);
extern i16 WINAPI MDAQ_Clear (
	i16        slot);
extern i16 WINAPI MDAQ_Get (
	i16        slot,
	i16        scansOrFrames,
	i16        getOrTap,
	u32        numToGet,
	u32        startFrame,
	u32        startScan,
	i32        timeout,
	i16        FAR * getBuffer,
	u32        FAR * numGotten,
	u32        FAR * lastFrame,
	u32        FAR * lastScan,
	i16        FAR * acqDone);
extern i16 WINAPI MDAQ_ScanRate (
	i16        slot,
	u16        interval,
	i16        timebase);
extern i16 WINAPI MDAQ_Setup (
	i16        slot,
	u32        bufferSize,
	i16        scansOrFrames,
	u32        preTrigScans,
	u32        postTrigScans,
	i16        FAR * acqBuffer);
extern i16 WINAPI MDAQ_Start (
	i16        slot,
	u32        numTriggers);
extern i16 WINAPI MDAQ_Stop (
	i16        slot);
extern i16 WINAPI MDAQ_StrGet (
	i16        slot,
	i16        scansOrFrames,
	i16        getOrTap,
	u32        numToGet,
	u32        startFrame,
	u32        startScan,
	i32        timeout,
	i8         FAR * getBuffer,
	u32        FAR * numGotten,
	u32        FAR * lastFrame,
	u32        FAR * lastScan,
	i16        FAR * acqDone);
extern i16 WINAPI MDAQ_Trig_Delay (
	i16        slot,
	u16        postTrigDelay,
	i16        timebase);
extern i16 WINAPI MDAQ_Trig_Select (
	i16        slot,
	i16        dTrigMode,
	i16        dEdge,
	i16        aTrigMode,
	i16        aSlope,
	i16        aLevel,
	i16        aTrigChan);
extern i16 WINAPI MIO_Calibrate (
	i16        slot,
	i16        calOP,
	i16        saveNewCal,
	i16        EEPROMloc,
	i16        CalRefChan,
	i16        DAC0Chan,
	i16        DAC1Chan,
	f64        calRefVolts,
	i16        refLoc);
extern i16 WINAPI MIO_Config (
	i16        slot,
	i16        dither,
	i16        useAMUX);
extern i16 WINAPI NI_DAQ_Mem_Alloc (
	i16        FAR * handle,
	i16        elementSize,
	u32        numElements,
	i16        memType,
	i16        memSource);
extern i16 WINAPI NI_DAQ_Mem_Attributes (
	i16        handle,
	i16        FAR * elementSize,
	u32        FAR * numElements,
	i16        FAR * lockCnt,
	i16        FAR * memType,
	i16        FAR * memSource);
extern i16 WINAPI NI_DAQ_Mem_Copy (
	i16        handle,
	i16        FAR * buffer,
	u32        startIndex,
	u32        numEl,
	i16        CopyDirection);
extern i16 WINAPI NI_DAQ_Mem_Free (
	i16        handle);
extern i16 WINAPI NI_DAQ_Mem_Lock (
	i16        handle,
	u32        FAR * address);
extern i16 WINAPI NI_DAQ_Mem_Unlock (
	i16        handle);
extern i16 WINAPI Peek_DAQ_Event (
	u32        timeOut,
	i16        FAR * handle,
	i16        FAR * msg,
	i16        FAR * wParam,
	i32        FAR * lParam);
extern i16 WINAPI RTSI_Clear (
	i16        slot);
extern i16 WINAPI RTSI_Clock (
	i16        slot,
	i16        connect,
	i16        direction);
extern i16 WINAPI RTSI_Conn (
	i16        slot,
	i16        brdSignal,
	i16        busLine,
	i16        direction);
extern i16 WINAPI RTSI_DisConn (
	i16        slot,
	i16        brdSignal,
	i16        busLine);
extern i16 WINAPI SC_2040_Config (
	i16        deviceNumber,
	i16        channel,
	i16        sc2040Gain);
extern i16 WINAPI SCAN_Demux (
	i16        FAR * buffer,
	u32        cnt,
	i16        numChans,
	i16        muxMode);
extern i16 WINAPI SCAN_Op (
	i16        slot,
	i16        numChans,
	i16        FAR * chans,
	i16        FAR * gains,
	i16        FAR * buffer,
	u32        cnt,
	f64        sampleRate,
	f64        scanRate);
extern i16 WINAPI SCAN_Sequence_Demux (
	i16        numChans,
	i16        FAR * chanVector,
	u32        bufferSize,
	i16        FAR * buffer,
	i16        samplesPerSequence,
	i16        FAR * scanSequenceVector,
	u32        FAR * samplesPerChanVector);
extern i16 WINAPI SCAN_Sequence_Retrieve (
	i16        deviceNumber,
	i16        samplesPerSequence,
	i16        FAR * scanSequenceVector);
extern i16 WINAPI SCAN_Sequence_Setup (
	i16        deviceNumber,
	i16        numChans,
	i16        FAR * chanVector,
	i16        FAR * gainVector,
	i16        FAR * scanRateDivVector,
	i16        FAR * scansPerSequence,
	i16        FAR * samplesPerSequence);
extern i16 WINAPI SCAN_Setup (
	i16        slot,
	i16        num_chans,
	i16        FAR * chans,
	i16        FAR * gains);
extern i16 WINAPI SCAN_Start (
	i16        slot,
	i16        FAR * buffer,
	u32        cnt,
	i16        tb1,
	u16        si1,
	i16        tb2,
	u16        si2);
extern i16 WINAPI SCAN_to_Disk (
	i16        slot,
	i16        numChans,
	i16        FAR * chans,
	i16        FAR * gains,
	i8         FAR * fileName,
	u32        cnt,
	f64        sampleRate,
	f64        scanRate,
	i16        concat);
extern i16 WINAPI Calibrate_1200 (
	i16        deviceNumber,
	i16        calOP,
	i16        saveNewCal,
	i16        EEPROMloc,
	i16        calRefChan,
	i16        grndRefChan,
	i16        DAC0chan,
	i16        DAC1chan,
	f64        calRefVolts,
	f64        gain);
extern i16 WINAPI SCXI_AO_Write (
	i16        chassisID,
	i16        module,
	i16        DACchannel,
	i16        rangeCode,
	i16        opCode,
	f64        voltCurrentData,
	i16        binaryDat,
	i16        FAR * binaryWritten);
extern i16 WINAPI SCXI_Cal_Constants (
	i16        chassisID,
	i16        module,
	i16        SCXIchannel,
	i16        operation,
	i16        calArea,
	i16        rangeCode,
	f64        SCXIgain,
	i16        DAQdevice,
	i16        DAQchannel,
	i16        DAQgain,
	f64        TBgain,
	f64        volt1,
	f64        binary1,
	f64        volt2,
	f64        binary2,
	f64        FAR * binEEprom1,
	f64        FAR * binEEprom2);
extern i16 WINAPI SCXI_Calibrate_Setup (
	i16        chassisID,
	i16        module,
	i16        calOp);
extern i16 WINAPI SCXI_Change_Chan (
	i16        chassisID,
	i16        module,
	i16        chan);
extern i16 WINAPI SCXI_Configure_Filter (
	i16        chassisID,
	i16        module,
	i16        channel,
	i16        filterMode,
	f64        freq,
	u16        cutoffDivDown,
	u16        outClkDivDown,
	f64        FAR * actFreq);
extern i16 WINAPI SCXI_Get_Chassis_Info (
	i16        chassisID,
	i16        FAR * chassisType,
	i16        FAR * address,
	i16        FAR * commMode,
	i16        FAR * commPath,
	i16        FAR * numSlots);
extern i16 WINAPI SCXI_Get_Module_Info (
	i16        chassisID,
	i16        slot,
	i32        FAR * modulePresent,
	i16        FAR * opMode,
	i16        FAR * DAQboard);
extern i16 WINAPI SCXI_Get_State (
	i16        chassisID,
	i16        module,
	i16        port,
	i16        channel,
	u32        FAR * data);
extern i16 WINAPI SCXI_Get_Status (
	i16        chassisID,
	i16        module,
	i16        wait,
	u32        FAR * data);
extern i16 WINAPI SCXI_Load_Config (
	i16        chassisID);
extern i16 WINAPI SCXI_MuxCtr_Setup (
	i16        slot,
	i16        enable,
	i16        scanDiv,
	u16        muxCtrVal);
extern i16 WINAPI SCXI_Reset (
	i16        chassisID,
	i16        moduleSlot);
extern i16 WINAPI SCXI_Scale (
	i16        chassisID,
	i16        module,
	i16        SCXIchannel,
	f64        SCXIgain,
	f64        TBgain,
	i16        DAQdevice,
	i16        DAQchannel,
	i16        DAQgain,
	u32        numPoints,
	i16        FAR * binArray,
	f64        FAR * voltArray);
extern i16 WINAPI SCXI_SCAN_Setup (
	i16        chassisID,
	i16        numModules,
	i16        FAR * modules,
	i16        FAR * numChans,
	i16        FAR * startChans,
	i16        DAQboard,
	i16        modeFlag);
extern i16 WINAPI SCXI_Set_Config (
	i16        chassisID,
	i16        chassisType,
	i16        address,
	i16        commMode,
	i16        slotOrCOMM,
	i16        numSlots,
	i32        FAR * moduleTypes,
	i16        FAR * opModes,
	i16        FAR * DAQboards);
extern i16 WINAPI SCXI_Set_Gain (
	i16        chassisID,
	i16        module,
	i16        channel,
	f64        gain);
extern i16 WINAPI SCXI_Set_Input_Mode (
	i16        chassisID,
	i16        module,
	i16        inputMode);
extern i16 WINAPI SCXI_Set_State (
	i16        chassisID,
	i16        module,
	i16        port,
	i16        channel,
	u32        data);
extern i16 WINAPI SCXI_Single_Chan_Setup (
	i16        chassisID,
	i16        module,
	i16        chan,
	i16        DAQboard);
extern i16 WINAPI SCXI_Track_Hold_Control (
	i16        chassisID,
	i16        module,
	i16        state,
	i16        DAQboard);
extern i16 WINAPI SCXI_Track_Hold_Setup (
	i16        chassisID,
	i16        module,
	i16        mode,
	i16        source,
	i16        send,
	i16        holdCnt,
	i16        DAQboard);
extern i16 WINAPI Select_Signal (
	i16        deviceNumber,
	u32        signal,
	u32        source,
	u32        sourceSpec);
extern i16 WINAPI Set_DAQ_Device_Info (
	i16        deviceNumber,
	u32        infoType,
	u32        infoVal);
extern i16 WINAPI Timeout_Config (
	i16        slot,
	i32        numTicks);
extern i16 WINAPI Trigger_Window_Config (
	i16        slot,
	i16        mode,
	u16        windowSize);
extern i16 WINAPI WFM_Chan_Control (
	i16        slot,
	i16        channel,
	i16        operation);
extern i16 WINAPI WFM_Check (
	i16        slot,
	i16        channel,
	i16        FAR * status,
	u32        FAR * pointsDone,
	u32        FAR * itersDone);
extern i16 WINAPI WFM_ClockRate (
	i16        slot,
	i16        group,
	i16        whickClock,
	i16        timebase,
	u32        updateInterval,
	i16        mode);
extern i16 WINAPI WFM_DB_Config (
	i16        slot,
	i16        numChans,
	i16        FAR * chanVect,
	i16        DBMode,
	i16        oldDataStop,
	i16        partialTransfer);
extern i16 WINAPI WFM_DB_HalfReady (
	i16        slot,
	i16        numChans,
	i16        FAR * chanVect,
	i16        FAR * halfReady);
extern i16 WINAPI WFM_DB_Transfer (
	i16        slot,
	i16        numChans,
	i16        FAR * chanVect,
	i16        FAR * buffer,
	u32        cnt);
extern i16 WINAPI WFM_DB_StrTransfer (
	i16        slot,
	i16        numChans,
	i16        FAR * chanVect,
	i8         FAR * strBuffer,
	u32        cnt);
extern i16 WINAPI WFM_from_Disk (
	i16        slot,
	i16        numChans,
	i16        FAR * chanVect,
	i8         FAR * fileName,
	u32        startPts,
	u32        endPts,
	u32        iterations,
	f64        rate);
extern i16 WINAPI WFM_Group_Control (
	i16        slot,
	i16        group,
	i16        operation);
extern i16 WINAPI WFM_Group_Setup (
	i16        slot,
	i16        numChans,
	i16        FAR * chanVect,
	i16        group);
extern i16 WINAPI WFM_Load (
	i16        slot,
	i16        numChans,
	i16        FAR * chanVect,
	i16        FAR * buffer,
	u32        cnt,
	u32        iterations,
	i16        mode);
extern i16 WINAPI WFM_Op (
	i16        slot,
	i16        numChans,
	i16        FAR * chanVect,
	i16        FAR * buffer,
	u32        cnt,
	u32        iterations,
	f64        rate);
extern i16 WINAPI WFM_Rate (
	f64        rate,
	i16        units,
	i16        FAR * timebase,
	u32        FAR * updateInterval);
extern i16 WINAPI WFM_Scale (
	i16        slot,
	i16        chan,
	u32        cnt,
	f64        gain,
	f64        FAR * voltArray,
	i16        FAR * binArray);
extern i16 WINAPI AI_Read_Scan (
	i16        slot,
	i16        FAR * reading);
extern i16 WINAPI AI_VRead_Scan (
	i16        slot,
	f64        FAR * reading);
extern i16 WINAPI AO_VScale (
	i16        slot,
	i16        chan,
	f64        voltage,
	i16        FAR * value);
extern i16 WINAPI GPCTR_Change_Parameter (
	i16        deviceNumber,
	u32        gpCounterNumber,
	u32        paramID,
	u32        paramValue);



/* Obsolete Functions */


extern i16 WINAPI REG_Level_Read (
	i16        slot,
	i16        registerIndex,
	u32        FAR * registerValue);
extern i16 WINAPI REG_Level_Write (
	i16        slot,
	i16        registerIndex,
	u32        bitsAffected,
	u32        bitSettings,
	u32        FAR * registerValue);
extern i16 WINAPI USE_E_Series (
	void);
extern i16 WINAPI USE_E_Series_AI (
	void);
extern i16 WINAPI USE_E_Series_AO (
	void);
extern i16 WINAPI USE_E_Series_DIO (
	void);
extern i16 WINAPI USE_E_Series_GPCTR (
	void);
extern i16 WINAPI USE_E_Series_GPCTR_Simple (
	void);
extern i16 WINAPI USE_E_Series_Misc (
	void);
extern i16 WINAPI USE_E_Series_WFM (
	void);
extern i16 WINAPI USE_E_Series_DAQ (
	void);
#ifdef WIN16
extern i16 WINAPI USE_A2XXX (
	void);
#endif /* WIN16 */
#ifdef WIN16
extern i16 WINAPI USE_MIO (
	void);
#endif /* WIN16 */
#ifdef WIN16
extern i16 WINAPI USE_LPM (
	void);
#endif /* WIN16 */
#ifdef WIN16
extern i16 WINAPI USE_LAB (
	void);
#endif /* WIN16 */
#ifdef WIN16
extern i16 WINAPI USE_DSP2200 (
	void);
#endif /* WIN16 */
#ifdef WIN16
extern i16 WINAPI USE_DIO_96 (
	void);
#endif /* WIN16 */
#ifdef WIN16
extern i16 WINAPI USE_DIO_32F (
	void);
#endif /* WIN16 */
#ifdef WIN16
extern i16 WINAPI USE_DIO_24 (
	void);
#endif /* WIN16 */
#ifdef WIN16
extern i16 WINAPI USE_AO_610 (
	void);
#endif /* WIN16 */
#ifdef WIN16
extern i16 WINAPI USE_AO_2DC (
	void);
#endif /* WIN16 */


#ifdef __cplusplus
}
#endif

#ifdef __locallydefinedFAR
#undef __locallydefinedFAR
#undef FAR
#endif



