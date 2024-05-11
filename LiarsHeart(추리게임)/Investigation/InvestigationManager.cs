using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class LocationData
{
    [SerializeField] private string locationName;
    public string LocationName { get => locationName; }

    [SerializeField] private GameObject spriteImage; 
    public GameObject SpriteImage { get => spriteImage; }
}

public class InvestigationManager : Singleton<InvestigationManager>
{
    [SerializeField] private List<LocationData> locationDatas;
    public List<LocationData> LocationDatas { get => locationDatas; }

    // Broadcasting
    [SerializeField] private StringEventChannelSO addLocationEvent;
    [SerializeField] private GameObjectEventChannelSO changeLocationEvent;

    // Listening
    [SerializeField] private IntEventChannelSO setDropdownValueEvent;
    [SerializeField] private VoidEventChannelSO onInvestigationUIEvent;

    const string path = "Events/Investigation/";

    protected override void Awake()
    {
        base.Awake();
        setDropdownValueEvent = Resources.Load<IntEventChannelSO>(path + "SetDropdownValueEvent");
        addLocationEvent = Resources.Load<StringEventChannelSO>(path + "AddLocationEvent");
        changeLocationEvent = Resources.Load<GameObjectEventChannelSO>(path + "ChangeLocationEvent");
        onInvestigationUIEvent = Resources.Load<VoidEventChannelSO>(path + "OnInvestigationUIEvent");
    }

    private void OnEnable()
    {
        setDropdownValueEvent.OnEventRaised += SelectLocation;
        onInvestigationUIEvent.OnEventRaised += SetLocationData;
    }

    private void OnDisable()
    {
        setDropdownValueEvent.OnEventRaised -= SelectLocation;
        onInvestigationUIEvent.OnEventRaised -= SetLocationData;
    }

    private void SetLocationData()
    {
        foreach (LocationData data in locationDatas)
        {
            addLocationEvent.RaiseEvent(data.LocationName);
        }
    }

    private void SelectLocation(int idx)
    {
        changeLocationEvent.RaiseEvent(locationDatas[idx].SpriteImage);
    }
}
