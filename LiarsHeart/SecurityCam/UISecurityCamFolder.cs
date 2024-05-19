using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class UISecurityCamFolder : MonoBehaviour
{
    [SerializeField] private SecurityCamSO securityCamData;
    [SerializeField] private UIEventHandler eventHandler = default;
    private UISecurityCam SecurityCamUI;

    private void Awake()
    {
        eventHandler = Utility.GetOrAddComponent<UIEventHandler>(this.gameObject);
    }

    private void Start()
    {
        eventHandler.AddUIEvent(Click, EUIEventType.Click);
    }

    private void Click(PointerEventData eventData)
    {
        SecurityCamUI = GameManager.UI.LoadPopupUI<UISecurityCam>("SecurityCam");
        SecurityCamUI.SetVisible(true);
        SecurityCamManager.Instance.SetSecurityCamData(securityCamData);
        //SecurityCamUI.CreateDateButton(securityCamData);
        Debug.Log("Folder Click");
    }
}
