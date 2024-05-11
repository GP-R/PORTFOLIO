using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.UI;

public class UIInvestigation : UIPopup
{
    [SerializeField] private TMP_Dropdown selectLocation;
    [SerializeField] private TMP_Text Label;

    [SerializeField] private Transform viewportParent;
    [SerializeField] private GameObject locationImage;

    [SerializeField] private Button closeButton;

    // Broadcasting
    [SerializeField] private VoidEventChannelSO onInvestigationUIEvent;
    [SerializeField] private IntEventChannelSO setDropdownValueEvent;

    // Listening
    [SerializeField] private StringEventChannelSO addLocationEvent;
    [SerializeField] private GameObjectEventChannelSO changeLocationEvent;

    const string path = "Events/Investigation/";

    private void Awake()
    {
        setDropdownValueEvent = Resources.Load<IntEventChannelSO>(path + "SetDropdownValueEvent");
        addLocationEvent = Resources.Load<StringEventChannelSO>(path + "AddLocationEvent");
        changeLocationEvent = Resources.Load<GameObjectEventChannelSO>(path + "ChangeLocationEvent");
        onInvestigationUIEvent = Resources.Load<VoidEventChannelSO>(path + "OnInvestigationUIEvent");

        closeButton.onClick.AddListener(() => SetVisible(false));
    }

    private void OnEnable()
    {
        selectLocation.onValueChanged.AddListener((value) => setDropdownValueEvent.RaiseEvent(value));
        addLocationEvent.OnEventRaised += AddLocation;
        changeLocationEvent.OnEventRaised += ChangeImage;
        onInvestigationUIEvent.RaiseEvent();

        if (selectLocation.options.Count != 0)
        {
            setDropdownValueEvent.RaiseEvent(0);
            Label.text = selectLocation.options[0].text;
        }
    }

    private void OnDisable()
    {
        addLocationEvent.OnEventRaised -= AddLocation;
        changeLocationEvent.OnEventRaised -= ChangeImage;
    }

    public void AddLocation(string optionText)
    {
        TMP_Dropdown.OptionData newOption = new TMP_Dropdown.OptionData(optionText);

        selectLocation.options.Add(newOption);
    }

    public void ChangeImage(GameObject spriteImage)
    {
        if(locationImage != null)
        {
            Destroy(locationImage);
        }
        locationImage = Instantiate(spriteImage, viewportParent);
        locationImage.transform.SetAsFirstSibling();
    }
}
