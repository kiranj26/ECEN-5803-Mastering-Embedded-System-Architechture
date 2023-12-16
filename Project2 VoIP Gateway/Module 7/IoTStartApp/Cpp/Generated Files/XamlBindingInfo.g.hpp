﻿
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
#include "pch.h"


::XamlBindingInfo::XamlBindings::XamlBindings(::XamlBindingInfo::IXamlBindings* pBindings)
    : _pBindings(pBindings)
{
}

::XamlBindingInfo::XamlBindings::~XamlBindings()
{
    delete _pBindings;
}

void ::XamlBindingInfo::XamlBindings::Initialize()
{
    if (!this->_pBindings->IsInitialized())
    { 
        this->_pBindings->Update();
    }
}

void ::XamlBindingInfo::XamlBindings::Update()
{
    this->_pBindings->Update();
}

void ::XamlBindingInfo::XamlBindings::StopTracking()
{
    this->_pBindings->StopTracking();
}

void ::XamlBindingInfo::XamlBindings::Loading(::Windows::UI::Xaml::FrameworkElement^, ::Platform::Object^)
{
    this->Initialize();
}

void ::XamlBindingInfo::XamlBindings::DataContextChanged(::Windows::UI::Xaml::FrameworkElement^, ::Windows::UI::Xaml::DataContextChangedEventArgs^ args)
{
    if (this->_pBindings->SetDataRoot(args->NewValue))
    {
        this->Update();
    }
}

void ::XamlBindingInfo::XamlBindings::SubscribeForDataContextChanged(::Windows::UI::Xaml::FrameworkElement^ object)
{
    this->_pBindings->SubscribeForDataContextChanged(object, this);
}

void ::XamlBindingInfo::XamlBindings::Connect(int connectionId, ::Platform::Object^ target)
{
    this->_pBindings->Connect(connectionId, target);
}

bool ::XamlBindingInfo::XamlBindings::ProcessBinding(unsigned int)
{
    throw ref new ::Platform::NotImplementedException();
}

int ::XamlBindingInfo::XamlBindings::ProcessBindings(::Windows::UI::Xaml::Controls::ContainerContentChangingEventArgs^ args)
{
    return this->_pBindings->ProcessBindings(args);
}

void ::XamlBindingInfo::XamlBindings::ResetTemplate()
{
    this->_pBindings->ResetTemplate();
}

namespace XamlBindingInfo
{
    class IXamlBindingTracking
    {
    public:
        virtual void PropertyChanged(Platform::Object^ sender, ::Windows::UI::Xaml::Data::PropertyChangedEventArgs^ e) = 0;
        virtual void CollectionChanged(::Platform::Object^ sender, ::Windows::UI::Xaml::Interop::NotifyCollectionChangedEventArgs^ e) = 0;
        virtual void DependencyPropertyChanged(::Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyProperty^ prop) = 0;
        virtual void VectorChanged(::Platform::Object^ sender, ::Windows::Foundation::Collections::IVectorChangedEventArgs^ e) = 0;
    };

    ref class XamlBindingTracking sealed
    {
    internal:
        XamlBindingTracking()
        {
        }

        void SetListener(::XamlBindingInfo::IXamlBindingTracking* pBindings)
        {
            this->_pBindingsTrackingWeakRef = pBindings;
        }

        // Event handlers

        void PropertyChanged(Platform::Object^ sender, ::Windows::UI::Xaml::Data::PropertyChangedEventArgs^ e)
        {
            if (this->_pBindingsTrackingWeakRef)
            {
                this->_pBindingsTrackingWeakRef->PropertyChanged(sender, e);
            }
        }

        void CollectionChanged(::Platform::Object^ sender, ::Windows::UI::Xaml::Interop::NotifyCollectionChangedEventArgs^ e)
        {
            if (this->_pBindingsTrackingWeakRef)
            {
                this->_pBindingsTrackingWeakRef->CollectionChanged(sender, e);
            }
        }

        void DependencyPropertyChanged(::Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyProperty^ prop)
        {
            if (this->_pBindingsTrackingWeakRef)
            {
                this->_pBindingsTrackingWeakRef->DependencyPropertyChanged(sender, prop);
            }
        }


        // Listener update functions

        void UpdatePropertyChangedListener(::Windows::UI::Xaml::Data::INotifyPropertyChanged^ obj, ::Windows::UI::Xaml::Data::INotifyPropertyChanged^* pCache, ::Windows::Foundation::EventRegistrationToken* pToken)
        {
            if (*pCache != nullptr && !(*pCache)->Equals(obj))
            {
                (*pCache)->PropertyChanged -= *pToken;
                *pCache = nullptr;
            }

            if (*pCache == nullptr && obj != nullptr)
            {
                *pCache = obj;
                *pToken = obj->PropertyChanged += ref new ::Windows::UI::Xaml::Data::PropertyChangedEventHandler(
                    this, &::XamlBindingInfo::XamlBindingTracking::PropertyChanged);
            }
        }

        void UpdatePropertyChangedListener(::Windows::UI::Xaml::Data::INotifyPropertyChanged^ obj, ::Platform::WeakReference& cacheRef, ::Windows::Foundation::EventRegistrationToken* pToken)
        {
            ::Windows::UI::Xaml::Data::INotifyPropertyChanged^ cache = cacheRef.Resolve<::Windows::UI::Xaml::Data::INotifyPropertyChanged>();
            if (cache != nullptr && !cache->Equals(obj))
            {
                cache->PropertyChanged -= *pToken;
                cache = nullptr;
                cacheRef = nullptr;
            }

            if (cache == nullptr && obj != nullptr)
            {
                cacheRef = cache = obj;
                *pToken = obj->PropertyChanged += ref new ::Windows::UI::Xaml::Data::PropertyChangedEventHandler(
                    this, &::XamlBindingInfo::XamlBindingTracking::PropertyChanged);
            }
        }

        void UpdateCollectionChangedListener(::Windows::UI::Xaml::Interop::INotifyCollectionChanged^ obj, ::Windows::UI::Xaml::Interop::INotifyCollectionChanged^* pCache, ::Windows::Foundation::EventRegistrationToken* pToken)
        {
            if (*pCache != nullptr && !(*pCache)->Equals(obj))
            {
                (*pCache)->CollectionChanged -= *pToken;
                *pCache = nullptr;
            }

            if (*pCache == nullptr && obj != nullptr)
            {
                *pCache = obj;
                *pToken = obj->CollectionChanged += ref new ::Windows::UI::Xaml::Interop::NotifyCollectionChangedEventHandler(
                    this, &::XamlBindingInfo::XamlBindingTracking::CollectionChanged);
            }
        }

        void UpdateDependencyPropertyChangedListener(::Windows::UI::Xaml::DependencyObject^ obj, Windows::UI::Xaml::DependencyProperty^ property, ::Windows::UI::Xaml::DependencyObject^* pCache, INT64* pToken)
        {
            if (*pCache != nullptr && !(*pCache)->Equals(obj))
            {
                (*pCache)->UnregisterPropertyChangedCallback(property, *pToken);
                *pCache = nullptr;
            }

            if (*pCache == nullptr && obj != nullptr)
            {
                *pCache = obj;
                *pToken = obj->RegisterPropertyChangedCallback(property, ref new ::Windows::UI::Xaml::DependencyPropertyChangedCallback(
                    this, &::XamlBindingInfo::XamlBindingTracking::DependencyPropertyChanged));
            }
        }

        void UpdateDependencyPropertyChangedListener(::Windows::UI::Xaml::DependencyObject^ obj, Windows::UI::Xaml::DependencyProperty^ property, ::Platform::WeakReference& cacheRef, INT64* pToken)
        {
            ::Windows::UI::Xaml::DependencyObject^ cache = cacheRef.Resolve<::Windows::UI::Xaml::DependencyObject>();
            if (cache != nullptr && !cache->Equals(obj))
            {
                cache->UnregisterPropertyChangedCallback(property, *pToken);
                cache = nullptr;
                cacheRef = nullptr;
            }

            if (cache == nullptr && obj != nullptr)
            {
                cacheRef = cache = obj;
                *pToken = obj->RegisterPropertyChangedCallback(property, ref new ::Windows::UI::Xaml::DependencyPropertyChangedCallback(
                    this, &::XamlBindingInfo::XamlBindingTracking::DependencyPropertyChanged));
            }
        }


    private:
        IXamlBindingTracking* _pBindingsTrackingWeakRef = nullptr;
    };

    ref class XamlBindingSetters sealed
    {
    internal:
        static void Set_Windows_UI_Xaml_Controls_ItemsControl_ItemsSource(::Windows::UI::Xaml::Controls::ItemsControl^ obj, ::Platform::Object^ value, ::Platform::String^ targetNullValue)
        {
            if (value == nullptr && targetNullValue != nullptr)
            {
                value = (::Platform::Object^) ::Windows::UI::Xaml::Markup::XamlBindingHelper::ConvertValue(::Platform::Object::typeid, targetNullValue);
            }
            obj->ItemsSource = value;
        }
    };

    template <typename T>
    struct ResolveHelper
    {
        static T^ Resolve(const ::Platform::WeakReference& wr)
        {
            return wr.Resolve<T>();
        }
    };

    template <>
    struct ResolveHelper<::Platform::String>
    {
        typedef ::Platform::IBox<::Platform::String^> ResolveType;

        static ::Platform::String^ Resolve(const ::Platform::WeakReference& wr)
        {
            return safe_cast<::Platform::String^>(wr.Resolve<ResolveType>());
        }

    };

    template<class T> 
    class XamlBindingsBase : public IXamlBindings
    {
    private:
        ::Platform::WeakReference _dataRoot;

    protected:
        bool _isInitialized;
        ::XamlBindingInfo::XamlBindingTracking^ _bindingsTracking;
        ::Windows::Foundation::EventRegistrationToken _dataContextChangedToken;
        static const int NOT_PHASED = (1 << 31);
        static const int DATA_CHANGED = (1 << 30);

    protected:
        XamlBindingsBase()
            : _isInitialized(false)
            , _bindingsTracking(nullptr)
        {
            _dataContextChangedToken.Value = 0;
        }

        virtual ~XamlBindingsBase()
        {
            if (_bindingsTracking != nullptr)
            {
                _bindingsTracking->SetListener(nullptr);
                _bindingsTracking = nullptr;
            }
        }
    
    public:
        T^ GetDataRoot()
        {
            return ResolveHelper<T>::Resolve(this->_dataRoot);
        }

        bool SetDataRoot(::Platform::Object^ data)
        {
            if (data != nullptr)
            {
                this->_dataRoot = data;
                return true;
            }
            return false;
        }

        void InitializeTracking(::XamlBindingInfo::IXamlBindingTracking* pBindingsTracking)
        {
            _bindingsTracking = ref new ::XamlBindingInfo::XamlBindingTracking();
            _bindingsTracking->SetListener(pBindingsTracking);
        }

        virtual void StopTracking() override
        {
            ReleaseAllListeners();
            this->_isInitialized = false;
        }

        virtual bool IsInitialized() override
        {
            return this->_isInitialized;
        }

        virtual void Update() override
        {
            this->Update_(this->GetDataRoot(), NOT_PHASED);
            this->_isInitialized = true;
        }

        void SubscribeForDataContextChanged(::Windows::UI::Xaml::FrameworkElement^ object, ::XamlBindingInfo::XamlBindings^ handler)
        {
            this->_dataContextChangedToken = object->DataContextChanged += 
                ref new Windows::Foundation::TypedEventHandler<::Windows::UI::Xaml::FrameworkElement^, ::Windows::UI::Xaml::DataContextChangedEventArgs^>(
                    handler, &::XamlBindingInfo::XamlBindings::DataContextChanged);
        }

        virtual void Connect(int connectionId, ::Platform::Object^ target) = 0;

        virtual void ResetTemplate()
        {
            // Overridden in the binding class as needed.
        }

        virtual int ProcessBindings(::Windows::UI::Xaml::Controls::ContainerContentChangingEventArgs^)
        {
            // Overridden in the binding class as needed.
            return -1;
        }

protected:
        virtual void Update_(T^ obj, int phase)
        {
            // Overridden in the binding class as needed.
            phase; // unreferenced parameter
        }

        virtual void ReleaseAllListeners()
        {
            // Overridden in the binding class as needed.
        }
    };
}


