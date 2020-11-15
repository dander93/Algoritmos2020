#pragma once
#ifndef _LISTHELPER_
#define _LISTHELPER_

#include "Ventas.h"

namespace ListHelper
{
	/**
	 * @brief Tipo de nodo de lista
	 * @tparam T El tipo de lista
	*/
	template <typename T>
	struct ListNode {
		T data;
		ListNode<T>* next;
	};

	/**
	 * @brief Inicializa la lista
	 * @tparam T El tipo de lista
	 * @param pointer La raiz de la lista
	*/
	template <typename T>
	void initList(ListNode<T>*& pointer) {
		pointer = NULL;
	}

	/**
	 * @brief Determina si la lista está vacía
	 * @tparam T El tipo de lista
	 * @param root La raiz de la lista
	 * @return True/False si la lista está vacía
	*/
	template <typename T>
	bool listIsEmpty(ListNode<T>* root) {
		return root == NULL;
	}

	/**
	 * @brief Insertar un elemento en la lista
	 * @tparam T El tipo de nodo a insertar en la lista
	 * @param root La raiz de la lista actual
	 * @param value El contenido del nodo a insertar
	*/
	template <typename T>
	void push(ListNode<T>*& root, T value) {
		//Creamos un nuevo nodo y obtenermos el puntero del mismo
		ListNode<T>* newPointer = new ListNode<T>();
		//Guardamos en el nuevo nodo la información que recibimos
		newPointer->data = value;
		//Guardamos en el siguiente del nuevo nodo el nodo anterior (o raiz)
		newPointer->next = root;
		//Convertimos el nuevo nodo en la raiz
		root = newPointer;

		/*
		* en pocas palabras sería:
		* nuevo nodoNuevo.siguiente = root actual(recibido)
		* root = nodoNuevo
		* */
	}

	/**
	 * @brief Elimina un nodo de la lista
	 * @tparam T El tipo del nodo a borrar de la lista
	 * @param root La raiz de la lista
	 * @return Devuelve el contenido del nodo eliminado
	*/
	template <typename T>
	T pop(ListNode<T>*& root) {
		//Creamos un nodo auxiliar del tipo pedido(T) y le asignamos la raiz
		ListNode<T>* nodoAuxiliar = root;
		//Guardamos la información de la raiz de tipo pedido(T)
		T data = nodoAuxiliar->data;
		//Hacemos que la raiz sea el contenido del siguiente de la raiz
		root = nodoAuxiliar->next;
		//Borramos el nodo auxiliar
		delete nodoAuxiliar;
		//Devolvemos la información del nodo borrado
		return data;
	}

	/**
	 * @brief Buscar en la lista según el criterio pedido
	 * @tparam T El tipo nodos de la lista
	 * @tparam K El tipo del valor a buscar
	 * @param root La raiz de la lista en la que se buscará
	 * @param value El valor a buscar
	 * @param criteria El criterio(función) que devuelve -1,0 o 1 por resultado de búsqueda
	 * @return El nodo en caso de ser encontrado sino NULL
	*/
	template <typename T, typename K>
	ListNode<T>* listSearch(ListNode<T>* root, K value, int (*criteria)(T, K)) {
		ListNode<T>* nodoEncontrado = NULL;

		//Creamos un nodo auxiliar para no jugar con la lista
		ListNode<T>* auxNode = root;

		//Mientras no se termine de recorrer o no lo haya encontrado
		while (auxNode != NULL && nodoEncontrado == NULL)
		{
			//Ejecutamos el criterio de búsqueda(si no encuentra debería devolver -1)
			if (criteria(auxNode->data, value) == 0)
			{
				//El criterio dió 0, por lo cual el nodo fue encontrado. Entonces nos lo guardamos como nodoEncontrado
				nodoEncontrado = auxNode;
			}
			//Tomamos el siguiente elemento de la lista para evaluarlo
			auxNode = auxNode->next;
		}

		//Devolvemos el nodo si lo encontramos o NULL
		return nodoEncontrado;
	}

	/**
	 * @brief Libera toda la memoria ocupada por la lista
	 * @tparam T El tipo de lista
	 * @param root La raiz de la lista
	*/
	template <typename T>
	void freeList(ListNode<T>*& root) {
		//Mientras la lista no esté vacía
		while (!listIsEmpty<T>(root))
		{
			//Eliminamos el nodo que contiene la raiz y no hacemos nada con la info resultante
			pop<T>(root);
		}
	}

	/**
	 * @brief Agrega al final de la lista un elemento
	 * @tparam T El tipo de la lista
	 * @param root La raiz de la lista
	 * @param value El elemento a agregar al final de la lista
	 * @return El puntero al nodo nuevo creado
	*/
	template <typename T>
	ListNode<T>* addToList(ListNode<T>*& root, T value) {

		//creo un nuevo nodo auxiliar
		ListNode<T>* newPointer = new ListNode<T>();
		//me guardo la información que viene en el nuevo nodo creado
		newPointer->data = value;

		//El guardo el puntero a la raiz en el nuevo nodo
		ListNode<T>* auxRootPointer = root;
		//Me creo un puntero auxiliar adicional para recorrer la lista
		ListNode<T>* prevPointer = NULL;

		//mientras la lista no esté vacía y no sea el final de la lista busco el siguiente elemento de la lista
		while (auxRootPointer != NULL)
		{
			//El puntero auxiliar(previo) se convierte en la nueva raiz
			prevPointer = auxRootPointer;
			//El puntero auxiliar se convierte en el que le sigue en la lista
			auxRootPointer = auxRootPointer->next;
		}

		//El nuevo puntero se convierte en el final de la lista
		newPointer->next = auxRootPointer;
		if (prevPointer == NULL)
		{
			//el nodo a enlazar va a quedar primero en la lista
			root = newPointer;
		}
		else
		{
			prevPointer->next = newPointer;
		}

		return newPointer;
	}

	/**
	 * @brief Inserta de forma ordenada en la lista
	 * @tparam T El tipo de la lista
	 * @param root La raiz de la lista
	 * @param value El valor a insertar
	 * @param criteria El criterio de ordenación
	 * @return El nuevo puntero a la lista
	*/
	template <typename T>
	ListNode<T>* orderedAddToList(ListNode<T>*& root, T value, int (*criteria)(T, T)) {
		ListNode<T>* newRoot = new ListNode<T>();
		newRoot->data = value;

		ListNode<T>* auxRoot = root;
		ListNode<T>* prevRoot = NULL;
		while (auxRoot != NULL && criteria(auxRoot->data, value) < 0)
		{
			prevRoot = auxRoot;
			auxRoot = auxRoot->next;
		}

		newRoot->next = auxRoot;
		if (prevRoot == NULL)
		{
			root = newRoot;
		}
		else
		{
			prevRoot->next = newRoot;
		}

		return newRoot;
	}

	/**
	 * @brief Ordena una lista
	 * @tparam T El tipo de la lista
	 * @param root La raiz de la lista
	 * @param criteria El criterio de ordenación
	*/
	template <typename T>
	void orderList(ListNode<T>*& root, int (*criteria)(T, T)) {
		ListNode<T>* auxRoot;
		initList<T>(auxRoot);

		while (!listIsEmpty<T>(root))
		{
			T data = pop<T>(root);
			orderedAddToList<T>(auxRoot, data, criteria);
		}

		root = auxRoot;
	}

	/**
	 * @brief Imprime la lista de la forma pasada por parámetro en howPrint
	 * @tparam T El tipo de la lista
	 * @param root La raiz de la lista
	 * @param howPrint La forma en la que se va a imprimir la lista
	*/
	template <typename T>
	void printList(ListNode<T>* root, void(*howToPrint)(ListNode<T>*& root)) {
		while (!listIsEmpty(root))
		{
			howToPrint(root);
		}
	}
}
#endif