using System.Collections.Generic;
using UnityEngine;

public class SecurityCamManager : Singleton<SecurityCamManager>
{
    [SerializeField] private List<SecurityCamSO> securityCamDatas;
    public List<SecurityCamSO> SecurityCamDatas { get => securityCamDatas; }

    [SerializeField] private SecurityCamSO curSecurityCam;
    public SecurityCamSO CurSecurityCam { get => curSecurityCam; }

    private List<ImageByTime> imageByTimes = new List<ImageByTime>();

    // Broadcasting
    [SerializeField] private SecurityCamEventChannelSO setSecurityCamEvent;
    [SerializeField] private ImageByTimesEventChannelSO setImageByTimeEvent;

    // Listening
    [SerializeField] private StringEventChannelSO onClickDateButtonEvent;

    const string path = "Events/SecurityCam/";

    protected override void Awake()
    {
        base.Awake();
        setSecurityCamEvent = Resources.Load<SecurityCamEventChannelSO>(path + "SetSecurityCamEvent");
        setImageByTimeEvent = Resources.Load<ImageByTimesEventChannelSO>(path + "SetImageByTimeEvent");
        onClickDateButtonEvent = Resources.Load<StringEventChannelSO>(path + "OnClickDateButtonEvent");
    }

    private void OnEnable()
    {
        onClickDateButtonEvent.OnEventRaised += SetImageByTimes;
    }

    private void OnDisable()
    {
        onClickDateButtonEvent.OnEventRaised -= SetImageByTimes;
    }

    public void SetSecurityCamData(SecurityCamSO data)
    {
        curSecurityCam = data;
        setSecurityCamEvent.RaiseEvent(data);
    }

    private void SetImageByTimes(string date)
    {
        imageByTimes = curSecurityCam.GetDateToImageByTimes(date);
        if(imageByTimes == null)
        {
            return;
        }
        setImageByTimeEvent.RaiseEvent(imageByTimes);
    }
}