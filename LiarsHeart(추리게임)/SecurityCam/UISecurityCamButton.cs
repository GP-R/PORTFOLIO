using UnityEngine;
using TMPro;
using UnityEngine.UI;

public class UISecurityCamButton : MonoBehaviour
{
    [SerializeField] private Toggle toggle;
    [SerializeField] private TMP_Text title;

    [SerializeField] private bool isSignal;
    public bool IsSignal { get => isSignal; }

    [SerializeField] UIEventHandler eventHandler;
    public UIEventHandler EventHandler { get => eventHandler; }

    private void Awake()
    {
        eventHandler = Utility.GetOrAddComponent<UIEventHandler>(this.gameObject);
    }

    private void Start()
    {

    }

    public void Init(string title, ToggleGroup toggleGroup)
    {
        this.title.text = title;
        this.toggle.group = toggleGroup;
    }

    // UI Event
    private void Click()
    {

    }
}
